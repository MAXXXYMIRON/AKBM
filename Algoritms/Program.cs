using System;
using System.Diagnostics;

namespace Algoritms
{
    class Program
    {
        static void Main(string[] args)
        {
            Stopwatch stopwatch = new Stopwatch();
            int index = 0;


            stopwatch.Start();
            index = Boyer_Mur.SearchSubString("МММаккксимккукссускккссс", "кккссс");
            stopwatch.Stop();

            Console.WriteLine($"В строке {"МММаккксимккукссускккссс"}, нашел индекс - {index},\n" +
                $"подстроки - {"кккссс"}, за {stopwatch.Elapsed.ToString()}");




            Console.ReadKey();
        }
    }
}
