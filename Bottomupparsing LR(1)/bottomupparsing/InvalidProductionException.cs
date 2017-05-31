using System;

namespace BottomUpParsing
{
    public class InvalidProductionException : Exception
    {
        public string Production { get; private set; }
        public string Cause { get; private set; }

        public InvalidProductionException(string production, string cause = null)
            : base(cause == null
                ? string.Format("Production \"{0}\" is invalid.", production)
                : string.Format("Production \"{0}\" is invalid : {1}", production, cause))
        {

        }
    }
}
