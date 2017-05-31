using System;
using System.Collections.Generic;
using System.Linq;

namespace BottomUpParsing
{
    public class GrammarResult
    {
        public List<string> TokensList { get; private set; } 
        public bool Accepted { get; private set; }
        public List<int> ProductionIndexes { get; private set; }
        public string Message { get; private set; }

        public GrammarResult(bool accepted, IEnumerable<int> productionIndexes, IEnumerable<string> tokensList, string message)
        {
            if (productionIndexes == null)
            {
                throw new ArgumentNullException("productionIndexes");
            }
            if (tokensList == null)
            {
                throw new ArgumentNullException("tokensList");
            }
            Accepted = accepted;
            ProductionIndexes = productionIndexes.ToList();
            TokensList = tokensList.ToList();
            Message = message;
        }
    }
}