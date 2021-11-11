# Warehouse-Stock-Manager
Project Report
Warehouse Stock Manager (WSM)

Synopsis:
	This program the project I made for my CSE Lab course. Hope you like it. This program contains all of the basic functions that are needed in a warehouse stock management system. The program is divided into 6 main parts:
  
The User Interface (UI) :- The UI has been carefully crafted to make it as easy for the user to use the program and use it to its full capacity. Most of the code is dedicated to the UI. It is also made to be as beautiful as possible.

preset1 (The ability to add new stock information into the inventory) :- With preset1 the user is asked to enter all the information about a stock which includes the item’s : ID, name, amount, cost price, minimum amount, and maximum amount. The user can add one stock at a time or multiple at one go. Extra code is included to make sure the information is provided correctly and to prevent wrong or conflicting inputs. The stock is then sorted with respect to its ID and added to a text file for storage. This happens for both preset2 and preset3.

preset2 (The ability to edit a stock information currently in the inventory) :- With this you can search for a particular stock and then edit any information you want. The same checks in preset1 are used here to make sure the information is valid. The search function is made to search for a stock: either through its ID, which is unique for all and uses binary search; or through its name, which is unique but there can be similar names like potato and potatochips; so, code has been added to show the various stocks with similar names and then allow the user to select the desired one. 

preset3 (The ability to remove a stock currently in the inventory) :- The same search function in preset2 is also used here. The user can thus select a stock and then remove it from the inventory.

preset4 (The ability to produce an order list for restocking the inventory) :- This part works by checking the current amount of all the stocks with its minimum amount. If the current amount of a stock is below the minimum amount of that stock, it orders the exact amount to fill the stock to its maximum amount again. This program then makes a new file called “restock.txt” where it creates a list which the user can copy paste the content in the text file into an email to your supplier, or just use it to see which stock you have a shortage on.

preset5 (The ability to see info about any or all the stocks in inventory) :- This program allows you to either look at all of the stocks currently in your inventory or look at stocks with an ID within a range selected by the user. It creates a beautiful table and prints the information in a way the user can easily understand. This program to print a table is also used in other parts like preset1, preset2, and preset3 for a better user experience.
