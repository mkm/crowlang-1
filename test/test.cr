f1() 42;
f2() if 0 then 2 else 3;
f3() if 1 then 2 else 3;
f4() let x = 8 in x;
f5(x)
        if equal(x, 0)
           then 0
           else if equal(x, 1)
                then 1
                else add(f5(sub(x, 1)), f5(sub(x, 2)));
f6(a, b) sub(add(a, b), 1);