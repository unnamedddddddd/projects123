arr = [1,2,3,4,5,6,7,8,9,10]

print('Предпоследний элемент list: ', arr[-2] );
print('Другие элементы list: ', arr[5], arr[6] );

arr[3] = 11

for i in range(4,8):
    print(f'Элемент с индеком {i}: {arr[i]}')
    
arr.append(12)

arr.insert(int((len(arr) - 1) / 2), 100)

count = 0;
for i in range(0,12):
    if arr[i] == 100:
        count += 1 
        
print(f'Число 100 в спике: {count} ')

newArr = arr.copy()
print(f'newArr равен arr: {newArr == arr}')