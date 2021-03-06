from functools import reduce
import timeit
# 1. 
# Вх: список чисел, Возвр: список чисел, где 
# повторяющиеся числа урезаны до одного 
# пример [0, 2, 2, 3] returns [0, 2, 3]. 

def rm_adj(nums):
    return reduce(lambda xs, x: xs if x in xs else xs + [x], nums, []);


# 2. Вх: Два списка упорядоченных по возрастанию, Возвр: новый отсортированный объединенный список
# ~ O(n log n)
def merge(lst1, lst2):
    return sorted(lst1 + lst2);

def merge2(a, b):
    l = []
    while a and b:
        if a[0] < b[0]:
            l.append(a.pop(0))
        else:
            l.append(b.pop(0))
    return l + a + b

def test_print(exp, res):
    print("Expected:");
    print(exp);
    print("Got:");
    print(res);

def test_1():
    nums = [0, 0, 0, 0]
    exp  = [0]
    res = rm_adj(nums)
    test_print(exp, res)
    nums = [0, 2, 2, 3]
    exp  = [0, 2, 3]
    res = rm_adj(nums)
    test_print(exp, res)

def test_2():
    lst1 = [0, 2, 4, 6]
    lst2 = [1, 3, 5]
    res = merge(lst1, lst2);
    exp = [0, 1, 2, 3, 4, 5, 6];
    test_print(exp, res);

    lst1 = [x for x in range(10**5)];
    lst2 = [x*5 for x in range(10**5)];

    start_time = timeit.default_timer();
    merge(lst1, lst2);
    print(timeit.default_timer() - start_time);

    start_time = timeit.default_timer();
    merge2(lst1, lst2);
    print(timeit.default_timer() - start_time);
   
def main():
    test_1()
    test_2()

if __name__ == '__main__':
  main()
