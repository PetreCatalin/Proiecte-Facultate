using System;
using System.Collections.Generic;
using System.Linq;

namespace BottomUpParsing
{
    internal static class Program
    {
        private static void Main(string[] args)
        {
            /*var grammar = new ContextIndependentGrammar(new List<string>
            {
                "E -> E '+' T",
                "E -> T",
                "T -> T '*' F",                
                "T -> F",
                "F -> 'a'"
            });
            var res = grammar.BottomUpParse("a*a".Select(c => c.ToString()));*/
            /*grammar = new ContextIndependentGrammar(new List<string>
            {
                "S -> S S",
                "S -> '(' ')'",
                "S -> '(' S ')'",
                "S -> '[' ']'",
                "S -> '[' S ']'"
            });
            var res = grammar.BottomUpParse("([[[()()[][]]]([])])".Select(c => c.ToString()));*/
            var grammar = new ContextIndependentGrammar(new List<string>
            {
                "S -> 'x'",
                "S -> 'y'",
                "S -> 'z'",
                "S -> S '+' S",
                "S -> S '-' S",
                "S -> S '*' S",
                "S -> S '/' S",
                "S -> '(' S ')'"
            });
            var res = grammar.BottomUpParse("( x - y + z ) / ( x + y ) - z * y / ( x + x - z * x / y ) + x * y - z".Split(' '));
            Console.WriteLine("Input : {0}", string.Join(" ", res.TokensList));
            Console.WriteLine("Accepted? : {0}", res.Accepted);
            foreach (var productionIndex in res.ProductionIndexes)
            {
                Console.WriteLine("{0}) {1}", productionIndex, grammar.Productions[productionIndex]);
            }
            Console.ReadKey();
        }
    }
}
