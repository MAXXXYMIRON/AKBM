using System.Collections.Generic;

namespace Algoritms
{
    static class Boyer_Mur
    {
        /// <summary>
        /// Получить индекс первого вхождения подстроки в строку,
        /// возврат -1 в случае неудачи.
        /// </summary>
        /// <param name="source">Исследуемая строка</param>
        /// <param name="template">Разыскиваемая подстрока</param>
        public static int SearchSubString(string source, string template)
        {
            int sLen = source.Length,
                tLen = template.Length;
            if (tLen > sLen) return -1;


            //Создадим таблицу стоп символов
            Dictionary<char, int> tableOfStopSymbols = new Dictionary<char, int>();
            for (int c = 0; c < sLen; c++)
            {
                tableOfStopSymbols[source[c]] = tLen;
            }
            for (int l = 0; l < tLen - 1; l++)
            {
                tableOfStopSymbols[template[l]] = tLen - l - 1;
            }


            int i = tLen - 1,
                j = i,
                k = i;
            //Смещаем шаблон на величину соответствующую стоп символу
            //и сравниваем символы с конца шаблона
            while(j >= 0 && i <= sLen - 1)
            {
                j = tLen - 1;
                k = i;
                while (j >= 0 && source[k] == template[j])
                {
                    k--;
                    j--;
                }
                i += tableOfStopSymbols[source[i]];
            }

            if(k >= sLen - tLen)
            {
                return -1;
            }
            else
            {
                return k + 1;
            }
        }
    }
}
