1. Создайте новый проект с типом Console Application.
2. Напишите программу, которая, используя метод Console.ReadLine(), вводит строку, содержащую три числа через пробел — сумму, процентную ставку (в процентах) и срок вклада, а потом на основе этих значений вычисляет накопившуюся сумму на момент окончания вклада. Результат нужно вывести на консоль.
3. Не забудьте выделить код, решающий задачу в отдельную от ввода и вывода функцию.

Детали:

1. В конце каждого месяца происходит капитализация — к сумме прибавляется накопившийся за месяц процент. Далее процент вычисляется от этой увеличенной суммы.
2. Процентная ставка — годовая (то есть в конце месяца сумма на счете увеличивается на одну двенадцатую ставки)
3. Считайте, что вклад открыт в первый день месяца, а срок вклада — это целое количество месяцев.
4. Код, решающий основную задачу нужно оформить в виде метода Calculate, принимающего строку, введенную пользователем. В этой задаче гарантируется, что ввод корректный.
