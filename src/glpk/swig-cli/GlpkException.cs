using System;

namespace org.gnu.glpk
{

    public class GlpkException: Exception
    {
        public GlpkException()
            {
            }

        public GlpkException(string message)
            : base(message)
        {
        }

        public GlpkException(string message, Exception inner)
            : base(message, inner)
        {
        }
    }
}