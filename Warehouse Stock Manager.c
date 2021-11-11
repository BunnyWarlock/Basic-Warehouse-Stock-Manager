#include <stdio.h>
#include <string.h>

typedef struct{
    int id,
        cost,
        amount,
        min, max;
    char name[21];
} item_info;

int choose_options (int, char []);

int confirmation (void);

void print_line (void);

void show_list (const item_info [], int, int, int);

void sortNprint (item_info [], int);

int binary_search (const item_info [], int, const char []);

int stock_search (const item_info [], int);

void preset1 (const item_info [], int);

void preset2 (item_info [], int);

void preset3 (item_info [], int);

void preset4 (item_info [], int);

int preset5 (const item_info [], int);

int main(void){
    FILE *filep;
    int mode, total_items, i;

    printf ("Welcome to the Warehouse Stock Management system. \n");
    printf ("\nHere you can add, edit, or remove any stock in your inventory. \n");
    printf ("\nYou can also set up minimum amount for each stocks, \n");
    printf ("to produce a list of stocks to buy, their amount, and total cost. \n");
    printf ("\nUse numbers to navigate through the program. \n");
    printf ("DON'T ENTER CHARACTERS AS INPUT FOR NAVIGATION! \n");
    printf ("DON'T EVER ENTER NEGATIVE NUMBERS AS INPUTS!!! \n");
    print_line();

    filep = fopen("current_stocks.txt", "r");
    if (filep == NULL){
        printf ("File \"current_stocks.txt\" not found... \n\n");
        printf ("Do you want to create the file \"current_stocks.txt\" ");
        if (confirmation()){
            filep = fopen("current_stocks.txt", "w");
            fprintf (filep, "0 \n");
            printf ("\nCreated file \"current_stocks.txt\". \n");
            printf ("Proceed as normal. \n");
            print_line();
        }
        else{
            printf ("\nProgram can't work without \"current_stocks.txt\"... \n");
            printf ("Closing Program. \n");
            print_line();
            return (0);
        }
    }
    fclose(filep);

    do{
        filep = fopen("current_stocks.txt", "r");
        fscanf (filep, "%d", &total_items);
        item_info current_inventory[total_items];
        for (i = 0; i < total_items; i++)
            fscanf (filep, "%d %s %d %d %d %d", &current_inventory[i].id, current_inventory[i].name, &current_inventory[i].amount,
                    &current_inventory[i].cost, &current_inventory[i].min, &current_inventory[i].max);
        fclose(filep);

        printf ("Features: \n");
        printf ("\t 1) Add a new stock to inventory \n");
        printf ("\t 2) Edit a stock currently in the inventory \n");
        printf ("\t 3) Remove a stock currently in the inventory \n");
        printf ("\t 4) Produce an order list for restocking \n");
        printf ("\t 5) See info about stocks in inventory \n");
        mode = choose_options(5, "feature");
        print_line();

        switch (mode){
            case 1:
                preset1(current_inventory, total_items); break;
            case 2:
                preset2(current_inventory, total_items); break;
            case 3:
                preset3(current_inventory, total_items); break;
            case 4:
                preset4(current_inventory, total_items); break;
            case 5:
                preset5(current_inventory, total_items); break;
        }
        print_line();
        printf ("Do you want to keep using the program ");
    } while (confirmation());

    printf ("Thank you for using our program. \n");
    print_line();
    return (0);
}

int choose_options(int x, char string[]){
    int n;
    printf ("\nWhich %s do you want to use? ", string);
    scanf ("%d", &n);
    if (n > x || n < 1){
        printf ("Invalid %s... Please Enter again. \n", string);
        n = choose_options(x, string);
    }

    return (n);
}

int confirmation(void){
    char in;
    printf ("( Y / N ): ");
    scanf (" %c", &in);
    printf ("\n");

    return (in == 'Y' || in == 'y');
}

void print_line(void){
    printf ("\n");
    for(int i = 0; i < 105; i++)
        printf ("=");
    printf ("\n\n");
}

void show_list (const item_info inventory[], int lower, int upper, int mode){
    int i;

    if (mode == 0 || mode == 1){
        printf ("\n");
        printf ("--------------------------------------------------------------------------------------------------------- \n");
        printf ("| ID \t| Item's Name           \t| Amount \t| Unit Cost \t| Min    \t| Max    \t| \n");
        printf ("|-------|-------------------------------|---------------|---------------|---------------|---------------| \n");
    }
    for (i = lower; i <= upper; i++)
        printf ("|%-2d \t| %-21s \t| %-6d \t| %-6d \t| %-6d \t| %-6d \t| \n", inventory[i].id, inventory[i].name,
                inventory[i].amount, inventory[i].cost, inventory[i].min, inventory[i].max);
    if (mode == 0)
        printf ("--------------------------------------------------------------------------------------------------------- \n\n");
}

void sortNprint(item_info final_inventory[], int total_items){
    FILE *filep;
    int i, j;
    item_info temp;

    for (i = 0; i < total_items; i++){
        for (j = i + 1; j < total_items; j++){
            if (final_inventory[i].id > final_inventory[j].id){
                temp = final_inventory[i];
                final_inventory[i] = final_inventory[j];
                final_inventory[j] = temp;
            }
        }
    }

    filep = fopen("current_stocks.txt", "w");
    fprintf (filep, "%d \n", total_items);
    for (i = 0; i < total_items; i++)
        fprintf (filep, "%d \t %-21s \t %d \t %d \t %d \t %d \n", final_inventory[i].id, final_inventory[i].name,
                 final_inventory[i].amount, final_inventory[i].cost, final_inventory[i].min, final_inventory[i].max);
    fclose(filep);
}

int binary_search (const item_info current_inventory[], int total_items, const char message[]){
    int first, last, mid, id, flag, index;

            do{
                flag = 0;
                first = 0;
                last = total_items - 1;

                printf ("%s", message);
                scanf ("%d", &id);
                while (!flag && first <= last){
                    mid = (first + last) / 2;
                    if (id == current_inventory[mid].id){
                        index = mid;
                        flag = 1;
                    }
                    else if (id < current_inventory[mid].id)
                        last = mid - 1;
                    else if (id > current_inventory[mid].id)
                        first = mid + 1;
                }
                if (!flag)
                    printf ("The item with ID (%d) does not exist in the inventory... \nTry Again. \n\n", id);
            } while (!flag);

            show_list(current_inventory, index, index, 0);
            return (index);
}

int stock_search (const item_info current_inventory[], int total_items){
    int mode, index;

    printf ("How would you like to search for the specific item: \n");
    printf ("\t 1) By Item ID \n");
    printf ("\t 2) By Item name \n");
    mode = choose_options(2, "option");

    switch (mode){
        case 1: ;
        printf ("\n");
            index = binary_search(current_inventory, total_items, "ID number of Item: ");
            break;

        case 2: ;
            char name[21];
            int multiple, count, flag, i;

            do{
                count = 0;
                flag = 0;
                multiple = 1;
                printf ("\nName of Item: ");
                scanf ("%s", name);
                name[20] = '\0';

                for (i = 0; i < total_items; i++){
                    if (strstr(current_inventory[i].name, name) != NULL){
                        show_list(current_inventory, i, i, multiple);
                        index = i;
                        flag = 1;
                        multiple = 2;
                        count++;
                    }
                }
                if (count > 0)
                    printf ("--------------------------------------------------------------------------------------------------------- \n\n");

                if (count > 1){
                    printf ("There were %d items with similar name. \n", count);
                    index = binary_search(current_inventory, total_items,
                                          "What is the ID of the item you were looking for (Use the above list as a guide): ");
                }

                if (!flag)
                    printf ("There is no item with this name (%s) in the inventory... \nTry Again. \n", name);
            } while (!flag);
            break;
    }

    return (index);
}

void preset1(const item_info current_inventory[], int total_items){
    FILE *filep;
    int i, j, n, flag;

    printf ("How many items do you wish to add: ");
    scanf ("%d", &n);
    item_info edit_inventory[n];
    for (i = 0; i < n; i++){
        printf ("\n===Item #%d=== \n", i + 1);

        do{
            flag = 0;
            printf ("Item ID (Only unique and non-negative ID) \t\t: ");
            scanf ("%d", &edit_inventory[i].id);
            for (j = 0; j < total_items; j++){
                if (edit_inventory[i].id == current_inventory[j].id){
                    printf ("\nAn item with ID (%d) already exists in the inventory... \n", edit_inventory[i].id);
                    show_list(current_inventory, j, j, 0);
                    printf ("Try Again. \n\n");
                    flag = 1;
                    break;
                }
            }
            for (j = 0; j < i; j++){
                if (edit_inventory[i].id == edit_inventory[j].id){
                    printf ("\nYou just added an item with the same ID (%d)... \n", edit_inventory[i].id);
                    show_list(edit_inventory, j, j, 0);
                    printf ("Try Again. \n\n");
                    flag = 1;
                    break;
                }
            }
        } while (flag);

        printf ("Item name (Max 20 characters with no spaces) \t\t: ");
        scanf ("%s", edit_inventory[i].name);
        edit_inventory[i].name[20] = '\0';

        printf ("Item amount in stock (No negative stocks) \t\t: ");
        scanf ("%d", &edit_inventory[i].amount);
        printf ("Item's cost price (No negative price) \t\t\t: ");
        scanf ("%d", &edit_inventory[i].cost);
        printf ("Minimum amount of the item allowed inside the inventory : ");
        scanf ("%d", &edit_inventory[i].min);
        do{
            flag = 0;
            printf ("Maximum amount of the item allowed inside the inventory : ");
            scanf ("%d", &edit_inventory[i].max);

            if (edit_inventory[i].max <= edit_inventory[i].min){
                printf ("Maximum amount of Items cannot be equal or less that the minimum amount of Items... \nTry Again. \n\n");
                flag = 1;
            }
        } while (flag);

        printf ("\nStock will be added once the program gets fully executed. \n");
    }
    printf ("\n%d Items added to the inventory. \n", n);
    show_list(edit_inventory, 0, n - 1, 0);

    total_items += n;
    item_info final_inventory[total_items];
    for (i = 0; i < total_items - n; i++)
        final_inventory[i] = current_inventory[i];
    for (i = 0; i < n; i++)
        final_inventory[total_items - n + i] = edit_inventory[i];
    sortNprint(final_inventory, total_items);
}

void preset2(item_info current_inventory[], int total_items){
    FILE *filep;
    int i, index, mode, flag;

    index = stock_search(current_inventory, total_items);

    printf ("What would you like to edit: \n");
    printf ("\t 1) The ID \n");
    printf ("\t 2) The Name \n");
    printf ("\t 3) The Amount \n");
    printf ("\t 4) The Cost Price \n");
    printf ("\t 5) The Minimum Amount \n");
    printf ("\t 6) The Maximum Amount \n");
    mode = choose_options(6, "option");

    switch (mode){
        case 1: ;
            int id;
            do{
                flag = 0;
                printf ("\nNew Item ID (Only unique and non-negative ID) \t\t: ");
                scanf ("%d", &id);
                for (i = 0; i < total_items; i++){
                    if (id == current_inventory[i].id){
                        printf ("\nAn item with ID (%d) already exists in the inventory... \n", id);
                        show_list(current_inventory, i, i, 0);
                        printf ("Try Again. \n");
                        flag = 1;
                        break;
                    }
                }

                if (!flag)
                   current_inventory[index].id = id;
            } while (flag);
            break;
        case 2:
            printf ("\nNew Item name (Max 20 characters with no spaces) \t\t: ");
            scanf ("%s", current_inventory[index].name);
            current_inventory[index].name[20] = '\0';
            break;
        case 3:
            printf ("\nNew Item amount in stock (No negative stocks) \t\t: ");
            scanf ("%d", &current_inventory[index].amount);
            break;
        case 4:
            printf ("\nNew Item's cost price (No negative price) \t\t\t: ");
            scanf ("%d", &current_inventory[index].cost);
            break;
        case 5:
            printf ("\nNew Minimum amount of the item allowed inside the inventory : ");
            scanf ("%d", &current_inventory[index].min);
            break;
        case 6: ;
            int max;
            do{
                flag = 0;
                printf ("\nNew Maximum amount of the item allowed inside the inventory : ");
                scanf ("%d", &max);

                if (max <= current_inventory[index].min){
                    printf ("Maximum amount of Items cannot be equal or less that the minimum amount of Items... \nTry Again. \n");
                    flag = 1;
                }

                if (!flag)
                    current_inventory[index].max = max;
            } while (flag);
            break;
    }

    printf ("\nThe Stock has been successfully edited. \n");
    show_list(current_inventory, index, index, 0);
    sortNprint(current_inventory, total_items);
}

void preset3(item_info current_inventory[], int total_items){
    int i, index, in, not = 0, correction = 0;

    printf ("How many stock are you going to delete: ");
    scanf ("%d", &in);
    for (i = 0; i < in; i++){
        printf ("\nItem #%d \n", i + 1);
        index = stock_search(current_inventory, total_items);
        printf ("Are you sure you want to delete this stock ");
        if (confirmation()){
            current_inventory[index].id = -1;
            strcpy (current_inventory[index].name, "-1");
            printf ("Stock will be deleted once the program gets fully executed. \n");
        }
        else{
            printf ("Stock not deleted. \n");
            not++;
        }
    }

    in -= not;
    item_info final_inventory[total_items - in];
    for (i = 0; i < total_items; i++){
            printf ("F");
        if (current_inventory[i].id != -1)
            final_inventory[i - correction] = current_inventory[i];
        else
            correction++;
    }
    sortNprint(final_inventory, total_items - in);
}

void preset4(item_info current_inventory[], int total_items){
    FILE *outp;
    int i, quantity, cost, total = 0;

    printf ("The program is currently making your order list for restocking your inventory. \n");
    printf ("This part works by checking the current amount of all the stocks with its minimum amount. \n");
    printf ("If the current amount is below the minimum amount, \n");
    printf ("It orders the exact amount to fill the stock to its maximum amount again. \n\n");

    outp = fopen("restock.txt", "w");
    fprintf (outp, "These Items are needed to restock the inventory. \n\n");
    fprintf (outp, "----------------------------------------------------------------- \n");
    fprintf (outp, "| Quantity \t| Item's Name           \t| Cost   \t| \n");
    fprintf (outp, "|---------------|-------------------------------|---------------| \n");

    for (i = 0; i < total_items; i++){
        if (current_inventory[i].amount <= current_inventory[i].min){
            quantity = current_inventory[i].max - current_inventory[i].amount;
            cost = current_inventory[i].cost * quantity;
            total += cost;
            fprintf (outp, "| %-6d \t| %-21s \t| %-6d \t| \n", quantity, current_inventory[i].name, cost);
        }
    }

    fprintf (outp, "----------------------------------------------------------------- \n");
    fprintf (outp, "                                          |Total| %-6d \t| \n", total);
    fprintf (outp, "                                          ----------------------- \n");
    fclose (outp);

    printf ("The order list has been created as file named \"restock\" in the same location as this program. \n");
    printf ("You can copy paste the content in the text file into an email to your supplier. \n");
    printf ("Or just use it to see which stock you have a shortage on. \n\n");

    printf ("Do you want the program to assume the ordered stocks arrived, \n");
    printf ("And update the inventory accordingly ");
    if (confirmation()){
        for (i = 0; i < total_items; i++){
        if (current_inventory[i].amount <= current_inventory[i].min)
            current_inventory[i].amount = current_inventory[i].max;
        }
        sortNprint(current_inventory, total_items);
        printf ("Done. \n");
    }

}

int preset5(const item_info current_inventory[], int total_items){
    int mode;

    printf ("There are currently %d amount of items in the stock. \n", total_items);
    if (total_items == 0){
        printf ("You can always add items in the inventory using function #1. \n");
        return (0);
    }
    printf ("\nDo you want to see: \n");
    printf ("\t 1) All of the items \n");
    printf ("\t 2) Items with ID within a set range (Inclusive) \n");
    mode = choose_options(2, "option");
    switch (mode){
        case 1:
            show_list(current_inventory, 0, total_items - 1, 0);
            break;
        case 2: ;
            int lower, upper, in, i;
            printf ("\nFrom ID# ");
            scanf ("%d", &in);
            for (i = 0; i < total_items; i++){
                if (current_inventory[i].id >= in){
                    lower = i;
                    break;
                }
            }
            printf ("  To ID# ");
            scanf ("%d", &in);
            for (i = total_items - 1; i >= 0; i--){
                if (current_inventory[i].id <= in){
                    upper = i;
                    break;
                }
            }
            show_list(current_inventory, lower, upper, 0);

    }

}
