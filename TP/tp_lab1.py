# TODO: tests, try block.

# 1. 
# Вх: список строк, Возвр: кол-во строк
# где строка > 2 символов и первый символ == последнему

def me(words):
  return len(list(filter(lambda str: len(str) > 2 and str[0] == str[-1], words)))


# 2. 
# Вх: список строк, Возвр: список со строками (упорядочено)
# за искл всех строк начинающихся с 'x', которые попадают в начало списка.
# ['tix', 'xyz', 'apple', 'xacadu', 'aabbbccc'] -> ['xacadu', 'xyz', 'aabbbccc', 'apple', 'tix']
def fx(words):
  return list(sorted(words, key=lambda s: (s[0] != 'x', s)));


# 3. 
# Вх: список непустых кортежей, 
# Возвр: список сортир по возрастанию последнего элемента в каждом корт.
# [(1, 7), (1, 3), (3, 4, 5), (2, 2)] -> [(2, 2), (1, 3), (3, 4, 5), (1, 7)]
def sort_by_sec(lst):
    return sorted(lst, key=lambda pair: bool(pair) and pair[-1])

def test(f, data, expected):

    print("Data:\n", data);
    res = f(data);
    print("Output:\n", res);
    print("Excepted:\n", expected);
    print("PASSED" if res == expected else "FAILED");
    print("");

def main():
    test(me, ['aa', 'ba', 'ca', 'acccca', 'bab', 'a'], 2);
    test(fx, ['tix', 'xyz', 'apple', 'xacadu', 'aabbbccc'],
            ['xacadu', 'xyz', 'aabbbccc', 'apple', 'tix']);
    test(sort_by_sec, [(1, 7), (1, 3), (3, 4, 5), (), (2, 2)],
                      [(), (2, 2), (1, 3), (3, 4, 5), (1, 7)]);

# Test
if __name__ == '__main__':
  main()
