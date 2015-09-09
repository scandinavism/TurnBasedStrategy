# TurnBasedStrategy
Economy-centric hexagonal grid Turn-Based Strategy with separate tactic combat screens, set in romantic-medieval world with no magic, revolving around attempts to unite 6 norse clans under one rule.

#Назначение
Этот репозиторий содержит проект, который я (Данила Никифоровский) разрабатываю для повышения квалификации и демонстрации своих возможностей потенциальным работодателям. Работа продолжается до сих пор, расширяя функциональность программы. Из-за того, что проект на данный момент не является законченным продуктом, могут присутствовать следующие недостатки:
* Присутствие "магических чисел"
* Нарушение правила сокрытия данных ООП

Данные недостатки планируется устранить 15 сентября на рефакторинг-сессии.

В текущий момент код программы демонстрирует следующие возможности:
* Работа с указателями
* Работа с классами
* Высокоуровневые шейдеры GLSL
* Поиск пути A* (A-star), с собственной реализацией очереди с приоритетом
* Создание генератора псевдослучайной последовательности конгурэнтным методом
* Основы 3D-графики (линейная алгебра)
* Использование шума Перлина для генерации карты

#Управление
* WASD для передвижения камеры
* колёсико мыши для масштабирования
* P - сменить точку назначения алгоритма поиска пути
* O - сменить точку старта алгоритма поиска пути
* ESC - выход

#Примечания
* Проект написан с использованием среды QtCreator. Файл проекта прилагается.
* Проект использует графический движок Irrlicht. Библиотеки приложены.
* Если вы попытаетесь собрать проект, то вам будет необходимо указать пути к библиотеке и заголовкам.
* Расположите Irrlich.dll, Irrlicht.ico и папку assets в одном уровне с исполняемым файлом
