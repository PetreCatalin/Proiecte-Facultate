using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;

namespace BottomUpParsing
{
    public class ContextIndependentGrammar
    {
        private readonly Dictionary<string , bool> _grammarValues;
        private readonly Dictionary<string, List<string>> _leftRightMapping;
        private readonly Dictionary<string, List<string>> _rightLeftMapping;
        private readonly Dictionary<string, int> _productionsIndexes; 
        private readonly List<Tuple<string, string>> _productions;

        public List<string> Terminals
        {
            get { return _grammarValues.Keys.SkipWhile(IsNonTerminal).ToList(); }
        }

        public List<string> NonTerminals
        {
            get { return _grammarValues.Keys.Where(IsNonTerminal).ToList(); }
        }

        public List<string> Productions
        {
            get { return _productions.Select(tupl => tupl.Item1 + " -> " + tupl.Item2).ToList(); }
        }

        private static bool IsNonTerminal(string value)
        {
            return value.First() == '\'' && value.Last() == '\'';
        }

        public ContextIndependentGrammar(IEnumerable<string> productions)
        {
            _grammarValues = new Dictionary<string, bool>();
            _leftRightMapping = new Dictionary<string, List<string>>();
            _rightLeftMapping = new Dictionary<string, List<string>>();
            _productions = new List<Tuple<string, string>>();
            _productionsIndexes = new Dictionary<string, int>();

            var multipleSpacesAndTabsRegex = new Regex("[ \t]{2,}", RegexOptions.Compiled);

            var productionIndex = 0;
            foreach (var production in productions)
            {
                var separated = Regex.Split(production, "->");
                
                if (separated.Length != 2)
                {
                    throw new InvalidProductionException(production, "Production has multiple \"->\" symbols or has none");
                }

                var left = multipleSpacesAndTabsRegex.Replace(separated[0].Trim(), " ");
                var right = multipleSpacesAndTabsRegex.Replace(separated[1].Trim(), " ");

                if (string.IsNullOrEmpty(left))
                {
                    throw new InvalidProductionException(production, "Production must not be empty on the left side of the \"->\"");
                }

                var splittedLeft = left.Split(' ');

                if (splittedLeft.Length != 1)
                {
                    throw new InvalidProductionException(production, "Production has multiple arguments or it's empty on the left side of the \"->\"");
                }

                var nonTerminal = splittedLeft[0];
                if (nonTerminal.First() == '\'' && nonTerminal.Last() == '\'')
                {
                    throw new InvalidProductionException(production, "Production must have a non terminal on the left side of the \"->\"");
                }
                _grammarValues[nonTerminal] = true;

                if (string.IsNullOrEmpty(right))
                {
                    throw new InvalidProductionException(production, "Production must not be empty on the right side of the \"->\"");
                }

                var rightSplitted = right.Split(' ');
                if (rightSplitted.Length == 0)
                {
                    throw new InvalidProductionException(production, "Production must not be empty on the right side of the \"->\"");
                }
                
                foreach (var chunk in rightSplitted)
                {
                    _grammarValues[chunk] = true;
                }

                if (!_leftRightMapping.ContainsKey(nonTerminal))
                {
                    _leftRightMapping[nonTerminal] = new List<string>();
                }
                _leftRightMapping[nonTerminal].Add(right);
                if (!_rightLeftMapping.ContainsKey(right))
                {
                    _rightLeftMapping[right] = new List<string>();
                }
                _rightLeftMapping[right].Add(nonTerminal);
                _productionsIndexes[nonTerminal + " -> " + right] = productionIndex;
                _productions.Add(new Tuple<string, string>(nonTerminal, right));
                productionIndex ++;
            }

            foreach (var productionLists in _leftRightMapping)
            {
                foreach (var tokenLists in productionLists.Value)
                {
                    foreach (var token in tokenLists.Split())
                    {
                        if (!_grammarValues.ContainsKey(token))
                        {
                            throw new InvalidProductionException(productionLists.Key + " -> " + tokenLists, "Production must contain valid and existing terminals and non terminals.");
                        }
                    }
                }
            }
        }

        public GrammarResult BottomUpParse(IEnumerable<string> inputTokens, bool printSteps = false)
        {
            var startStep = 1;
            var state = 'q';
            var position = 0;
            var currentDerivation = new Stack<string>();
            var operationsHistory = new Stack<object>();
            var literalTokens = inputTokens.Select(token => '\'' + token + '\'').ToList();

            Func<bool> reduce = () =>
            {
                if (state != 'q')
                {
                    return false;
                }
                var extractedSymbols = new List<string>();
                var usedSymbols = 0;
                string existentExpression = null;
                StringBuilder currentExpression = null;
                while (currentDerivation.Any())
                {
                    var tok = currentDerivation.Pop();
                    extractedSymbols.Add(tok);
                    if (currentExpression == null)
                    {
                        currentExpression = new StringBuilder(tok);
                    }
                    else
                    {
                        currentExpression.Insert(0, " ");
                        currentExpression.Insert(0, tok);
                    }
                    if (!_rightLeftMapping.ContainsKey(currentExpression.ToString()))
                    {
                        continue;
                    }
                    existentExpression = currentExpression.ToString();
                    usedSymbols = extractedSymbols.Count;
                }
                foreach (var tok in extractedSymbols.Skip(usedSymbols).AsEnumerable().Reverse())
                {
                    currentDerivation.Push(tok);
                }
                if (existentExpression == null)
                {
                    return false;
                }
                var keyValue = _rightLeftMapping[existentExpression];
                var firstProductionFound = keyValue[0];
                var productionIndex = _productionsIndexes[firstProductionFound + " -> " + existentExpression];
                currentDerivation.Push(firstProductionFound);
                operationsHistory.Push(productionIndex);
                state = 'q';
                return true;
            };

            Func<bool> getBackOne = () =>
            {
                if (state != 'r' || !currentDerivation.Any() || !operationsHistory.Any())
                {
                    return false;
                }
                var topSymbol = currentDerivation.Peek();
                if (!_leftRightMapping.ContainsKey(topSymbol))
                {
                    return false;
                }
                var topOperation = operationsHistory.Peek();
                if (!(topOperation is int))
                {
                    return false;
                }
                var productionIndex = (int)topOperation;
                if (productionIndex < 0 || productionIndex >= _productions.Count)
                {
                    return false;
                }
                if (_productions[productionIndex].Item1 != topSymbol)
                {
                    return false;
                }
                var currentDerivationClone = new List<string>(currentDerivation);
                currentDerivation.Pop();
                foreach (var chunk in _productions[productionIndex].Item2.Split(' '))
                {
                    currentDerivation.Push(chunk);
                }

                string newDerivation = null;
                while (currentDerivation.Any())
                {
                    var currentSymbol = currentDerivation.Pop();
                    if (newDerivation == null)
                    {
                        newDerivation = currentSymbol;
                    }
                    else
                    {
                        newDerivation = currentSymbol + " " + newDerivation;
                    }
                    if (!_rightLeftMapping.ContainsKey(newDerivation))
                    {
                        continue;
                    }

                    var leftParts = _rightLeftMapping[newDerivation];
                    foreach (var part in leftParts)
                    {
                        var newProductionIndex = _productionsIndexes[part + " -> " + newDerivation];
                        if (newProductionIndex <= productionIndex)
                        {
                            continue;
                        }
                        operationsHistory.Pop();
                        operationsHistory.Push(newProductionIndex);
                        currentDerivation.Push(part);
                        state = 'q';
                        return true;
                    }
                }
                foreach (var symbol in currentDerivationClone.AsEnumerable().Reverse())
                {
                    currentDerivation.Push(symbol);
                }
                return false;
            };

            Func<bool> getBackTwo = () =>
            {
                if (state != 'r' || !currentDerivation.Any() || !operationsHistory.Any() || position != literalTokens.Count)
                {
                    return false;
                }
                var topSymbol = currentDerivation.Peek();
                if (!_leftRightMapping.ContainsKey(topSymbol))
                {
                    return false;
                }
                var topOperation = operationsHistory.Peek();
                if (!(topOperation is int))
                {
                    return false;
                }
                var productionIndex = (int) topOperation;
                if (productionIndex < 0 || productionIndex >= _productions.Count)
                {
                    return false;
                }
                if (_productions[productionIndex].Item1 != topSymbol)
                {
                    return false;
                }
                currentDerivation.Pop();
                var splittedTokens = _productions[productionIndex].Item2.Split(' ');
                foreach (var token in splittedTokens)
                {
                    currentDerivation.Push(token);
                }
                operationsHistory.Pop();
                state = 'r';
                return true;
            };

            Func<bool> getBackThree = () =>
            {
                if (state != 'r' || !currentDerivation.Any() || !operationsHistory.Any() || position >= literalTokens.Count)
                {
                    return false;
                }
                var topSymbol = currentDerivation.Peek();
                if (!_leftRightMapping.ContainsKey(topSymbol))
                {
                    return false;
                }
                var topOperation = operationsHistory.Peek();
                if (!(topOperation is int))
                {
                    return false;
                }
                var productionIndex = (int)topOperation;
                if (productionIndex < 0 || productionIndex >= _productions.Count)
                {
                    return false;
                }
                if (_productions[productionIndex].Item1 != topSymbol)
                {
                    return false;
                }
                currentDerivation.Pop();
                var splittedTokens = _productions[productionIndex].Item2.Split();
                foreach (var token in splittedTokens)
                {
                    currentDerivation.Push(token);
                }
                currentDerivation.Push(literalTokens[position]);
                position++;
                operationsHistory.Pop();
                operationsHistory.Push('d');
                state = 'q';
                return true;
            };

            Func<bool> getBackFour = () =>
            {
                if (state != 'r' || position == 0 || !currentDerivation.Any() || !operationsHistory.Any())
                {
                    return false;
                }
                var topSymbol = currentDerivation.Peek();
                var topOperator = operationsHistory.Peek();
                if (!(topSymbol == literalTokens[position - 1] && topOperator is char && (char)topOperator == 'd'))
                {
                    return false;
                }
                currentDerivation.Pop();
                operationsHistory.Pop();
                position--;
                state = 'r';
                return true;
            };

            Func<bool> move = () =>
            {
                if (state != 'q' || position >= literalTokens.Count)
                {
                    return false;
                }
                currentDerivation.Push(literalTokens[position]);
                position++;
                operationsHistory.Push('d');
                return true;
            };

            Func<bool> prepareGetBack = () =>
            {
                if (state != 'q' || position != literalTokens.Count)
                {
                    return false;
                }
                state = 'r';
                return true;
            };

            Func<bool> accept = () =>
            {
                if (state != 'q' || position != literalTokens.Count || currentDerivation.Count != 1)
                {
                    return false;
                }
                state = 't';
                return true;
            };

            Func<bool> error = () =>
            {
                if (state != 'r' || position != 0 || currentDerivation.Any() || operationsHistory.Any())
                {
                    return false;
                }
                state = 'e';
                return true;
            };

            while (state != 't' && state != 'e')
            {
                if (startStep <= 1)
                {
                    if (reduce())
                    {
                        if (printSteps)
                        {
                            Console.WriteLine("1");                            
                        }
                        startStep = 1;
                        continue;
                    }
                }

                if (startStep <= 2)
                {
                    // Read a token and put it in stack.
                    if (move())
                    {
                        if (printSteps)
                        {
                            Console.WriteLine("2");
                        }
                        startStep = 1;
                        continue;
                    }
                }

                if (startStep <= 3)
                {
                    if (accept())
                    {
                        if (printSteps)
                        {
                            Console.WriteLine("3");
                        }
                        continue;
                    }
                }

                if (startStep <= 4)
                {
                    // Go back as we are in a dead end.
                    if (prepareGetBack())
                    {
                        if (printSteps)
                        {
                            Console.WriteLine("4");
                        }
                    }
                }

                if (startStep <= 5)
                {
                    if (getBackOne())
                    {
                        if (printSteps)
                        {
                            Console.WriteLine("5a");
                        }
                        startStep = 1;
                        continue;
                    }
                    if (getBackTwo())
                    {
                        if (printSteps)
                        {
                            Console.WriteLine("5b");
                        }
                        startStep = 5;
                        continue;
                    }
                    if (getBackThree())
                    {
                        if (printSteps)
                        {
                            Console.WriteLine("5c");
                        }
                        startStep = 1;
                        continue;
                    }
                    if (getBackFour())
                    {
                        if (printSteps)
                        {
                            Console.WriteLine("5d");
                        }
                        startStep = 5;
                        continue;
                    }
                    if (error())
                    {
                        if (printSteps)
                        {
                            Console.WriteLine("5e");
                        }
                    }
                }
            }
            return new GrammarResult(state == 't', operationsHistory.OfType<int>(), inputTokens, null);
        }
    }
}
