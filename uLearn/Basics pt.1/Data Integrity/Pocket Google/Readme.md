[Скачайте проект](https://ulearn.me/Exercise/StudentZip?courseId=BasicProgramming&slideId=5caa9930-a3af-4ba0-9a8e-761bb7cb0ec5)

В этом проекте вы создадите структуру данных индекса, который используется для быстрого поиска слов в документах.

В файле Indexer.cs реализуйте предложенные методы

* Add. Этот метод должен индексировать все слова в документе. Разделители слов: { ' ', '.', ',', '!', '?', ':', '-','\r','\n' }; Сложность – O(document.Length)

* GetIds. Этот метод должен искать по слову все id документов, где оно встречается. Сложность — O(result), где result — размер ответа на запрос

* GetPositions. Этот метод по слову и id документа должен искать все позиции, в которых слово начинается. Сложность — O(result)

* Remove. Этот метод должен удалять документ из индекса, после чего слова в нем искаться больше не должны. Сложность — O(document.Length)