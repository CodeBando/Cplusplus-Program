# CS-210 Project 3
# Matthew Bandyk
# Python file
# V1 - 12/11/2022

import re
import string

# function to display all types of items and number sold in the day
def ItemTotals():
    # opens file and reads it
    f = open('CS210_Project_Three_Input_File.txt', 'r') 
    products = f.read().splitlines()
    itemList = []
    itemTotal = []

    #loops through file and add's each type of item to the list itemList
    for i in products[:-1]: 
        if i not in itemList:
            itemList.append(i)

    # Sorts the itemList in alphabetical order
    itemList.sort() 

    # loops through list and then adds the total number of times the product was sold to the list itemTotal
    for i in itemList: 
        x = products.count(i)
        itemTotal.append(x)
    
    # creates dictonary with key, value of item type and item total respectively
    res = {itemList[i]: itemTotal[i] for i in range(len(itemList))}

    # display's the item list and totals sold
    print('Type of product sold and total number sold of each product')
    print('----------------------------------------------------------')
    for key, value in res.items():
        print('  {}\n  Total sold: {}\n'.format(key, value))

    f.close()

# function to return the number of an item sold during the day    
def SingleItem(v):
    # opens and reads file
    f = open('CS210_Project_Three_Input_File.txt', 'r')
    products = f.read().splitlines()
    itemList = []

    for i in products:
        itemList.append(i)
    
    # assigns x with the number of times the item was sold during the day based on user input
    x = itemList.count(v)

    f.close()

    return x;

# function to create a .dat file that houses the different types of products sold and the number of each type sold
def CreateDat():
    # Opens and reads file
    f = open('CS210_Project_Three_Input_File.txt', 'r')
    products = f.read().splitlines()
    itemList = []
    itemTotal = []

    for i in products[:-1]:
        if i not in itemList:
            itemList.append(i)

    itemList.sort()

    for i in itemList:
        x = products.count(i)
        itemTotal.append(x)
    
    res = {itemList[i]: itemTotal[i] for i in range(len(itemList))}

    f.close()

    # creates new .dat file and writes the product and product totals to it for use in C++ code
    w = open("frequency.dat", 'w') 
    for key, value in res.items(): 
        w.write('%s %s\n' % (key, value))

    w.close()