import re
import string

#Open and read grocery file, count each itertaion of item to print when requested
def read_File():
    
    ticket = open("ProduceList.txt") 
    products = ticket.read().split() #create object to hold line info from ticket object
    single_Product = sorted(set(products))
    for word in single_Product:
        print("------------------------------------")
        print("\n")
        print(products.count(word), " : ",  word)
        print("\n")
        print("------------------------------------")
    
    ticket.close() #closes ticket object to prevent memory issues

    
#Get string from user input on C++ side, search through text file, count occurances of each item, and print
def locate_Total_Product_Amount(v):

    ticket = open("ProduceList.txt")
    products = ticket.read().split() #creates object that holds each line info from ticket object
    single_Product = sorted(set(products)) #sort items
    ticket.close() #close ticket object to prevent memory issues
    
    tot = 0 #define total and send to C++
    tot_inventory = 0 #count loop iterations to find total inventory of item 
    tot_inventory_count = 0 #hold total inventory in document file

    for word in single_Product: #get total amount of items in list
        tot_inventory_count += 1

    for word in single_Product: #find indiviudal item requested by user
        temp_String = word.strip().lower()
        tot_inventory += 1
        if (temp_String == v):
            tot = products.count(word)
            tot_inventory -= 1 #determine item was accessed at least once during iteration. Determines if user input in file
        if (temp_String != v and tot_inventory == tot_inventory_count):
            return -1 # Return when user input not present in product list   
    
    return tot

#get info from text file, count and sort products, write counted and sorted list to .dat file, produce histogram of products
def read_AND_Write_File():

    ticket = open("ProduceList.txt")
    data = open("frequency.dat", "w")
    products = ticket.read().split() #creates object that holds each line info from ticket object
    single_Product = sorted(set(products)) #sorts products


    #write data to the .dat file
    for word in single_Product:
        data.write(word)
        data.write(" ")
        data.write(str(products.count(word))) #convert to string to write to .dat file
        data.write("\n")
    
    data.close() #close file

    histo_data = open("frequency.dat", "r") # read .dat file
    product_data = histo_data.readlines() #Read lines and find frequency of products
    #temp variables used for loops
    temp_freq = 0
    temp_product = ""

    #reads and prepares data from .dat file for histogram
    for line in product_data:
        temp_int = 0
        temp_string = line.split() #split product name and frequency
        for word in temp_string:
            temp_int += 1
            if (temp_int == 1):
                temp_product = word 
                print(temp_product, end = " ")
            if (temp_int == 2):
                temp_freq = int(word) #frequency of product
        

        #creates Histogram
        for i in range(temp_freq):
            print("*", end = "")
        print("\n")
        print("------------------------------------")
        print("\n")