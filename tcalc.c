#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <math.h>

//compile with gcc -Wall -g -lm calc.c -o calc `pkg-config --cflags --libs gtk+-2.0`
//declarations for the functions used 
int leftshift(double base);
void button0_callback();
void button1_callback();
void button2_callback();
void button3_callback ();
void button4_callback ();
void button5_callback();
void button6_callback();
void button7_callback();
void button8_callback();
void button9_callback();
void multiply_callback();
void add_callback();
void subtract_callback();
void divide_callback();
void equals_callback();
void clear_callback();
void decimal_callback();
void power_callback();
void squared_callback();
void squareroot_callback();
void secondary_callback(GtkWidget *button, guint data);
void main_callback(GtkWidget *fixed, guint data);
void main2_callback(GtkWidget *button, guint data);
void secondary2_callback(GtkWidget *button, guint data);
void decimalconvert ();
void decimaltooct ();
void decimaltobinary ();
void factorial_callback();
void conversion_callback(GtkWidget *label, guint data);
gboolean keyboard_callback (GtkWidget *widget, GdkEventKey *event, gpointer user_data);


//I need to find a way to fix this, this is a problem, variables are not supposed to be outside of main.
double num1, num2;
// possibly looking into bool functions for all of these
int multcount, addcount, subcount, divcount, placementcount, decimalcount, powercount, squaredcount,  squareroot, factorialcount;
int binarycount = 0, octcount = 0;
GtkWidget *display; //widget for the display 
GtkTextBuffer *buffer; //widget for the text 

int main(int argc, char *argv[])  //gotta start somewhere
{
GtkWidget *window; //widget for the window
GtkWidget *numberpad, *grid2, *grid3, *grid4;
GtkWidget *gridbox;
GtkWidget *gridvbox;
GtkWidget *vbox; //widget for the vertical box
GtkWidget *button; //widget for the buttons 
GtkCssProvider* Provider = gtk_css_provider_new();
GtkStyleContext *displaycontext, *buttoncontext, *windowcontext, *labelcontext, *menucontext;
GtkWidget *labels;
GtkWidget *conversionbox;
GtkWidget *menu;
GtkWidget *menu_bar;
GtkWidget *root_menu;

gchar *values[20] = {"%", "/", "*", "7", "8", "9","4", "5", "6","1", "2", "3"}; //labels for the buttons 

gchar *misc[2] = {"0", "."};

gchar *secondarys[20] = {"-", "+", "="};
gchar *secondarys2[20] = {"CE", "x2", "^", "sqrt", "Mod", "x!", "(", ")"};
gchar *conversions[4] = {"Dec", "Bin", "Hex", "Oct"};
gchar *headers [20] = {"File", "Edit", "Constants", "Settings", "Help"};
int i = 0; //rows
int j = 0; //columns
int pos = 0; //position in the array

gtk_init(&argc, &argv); //starting gtk 

window = gtk_window_new(GTK_WINDOW_TOPLEVEL); //creates toplevel window
gtk_window_set_title(GTK_WINDOW(window), "TCalc v.1.0"); //sets a window title 
gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER); //opens the window in the center of the screen
gtk_container_set_border_width(GTK_CONTAINER(window), 5); //sets the border size of the window
g_signal_connect(window, "key-release-event", G_CALLBACK(keyboard_callback), NULL);

menu = gtk_menu_new ();
menu_bar = gtk_menu_bar_new ();
char buf[128];
for (i = 0; i < 5; i++)
{
  sprintf (buf, "%s", headers[i]);
  root_menu = gtk_menu_item_new_with_label (buf);
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (root_menu), menu);
  gtk_menu_shell_append (GTK_MENU_SHELL (menu_bar), root_menu);
  menucontext = gtk_widget_get_style_context(root_menu);
  gtk_style_context_add_class(menucontext, "menu_style");
  gtk_style_context_add_provider (menucontext,GTK_STYLE_PROVIDER(Provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
}

display = gtk_text_view_new (); //sets the display widget as a text display 
buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (display)); //sets the buffer widget to the text buffer of display
gtk_widget_set_size_request(display, 150, 40); //sets the size of the display 

gtk_css_provider_load_from_path(GTK_CSS_PROVIDER(Provider), "Styles.css", NULL);
displaycontext = gtk_widget_get_style_context(display);
gtk_style_context_add_class(displaycontext, "display_style");
gtk_style_context_add_provider (displaycontext,GTK_STYLE_PROVIDER(Provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
windowcontext = gtk_widget_get_style_context(window);
gtk_style_context_add_class(windowcontext, "window_style");
gtk_style_context_add_provider (windowcontext,GTK_STYLE_PROVIDER(Provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
gtk_widget_add_events(window, GDK_KEY_PRESS_MASK);

numberpad= gtk_grid_new(); //sets the table widget as a 4x4 arrangement without autosizing

//these for loops are for creating the buttons and attaching them to their callbacks 
for (i=0; i < 4; i++) //for loop for the rows
{
for (j=0; j < 3; j++) //for loop for the columns
{
button = gtk_button_new_with_label(values[pos]); //sets each button label to the respective button 
main_callback(button, pos); //attaches the button to the respective callback
gtk_grid_attach(GTK_GRID(numberpad), button, j, i, 1, 1); //sets the defaults for creating each table button
gtk_widget_set_size_request(button, 40, 40); //sets the size of the buttons
buttoncontext = gtk_widget_get_style_context(button);
gtk_style_context_add_class(buttoncontext, "button_style");
gtk_style_context_add_provider (buttoncontext,GTK_STYLE_PROVIDER(Provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

pos++; //changes the position 
}
}
grid2 = gtk_grid_new();
pos = 0;
i = 0;
j = 0;

for (i=0; i < 3 ; i++) //for loop for the rows
{
for (j=0; j < 1; j++) //for loop for the columns
{
button = gtk_button_new_with_label(secondarys[pos]); //sets each button label to the respective button 
secondary_callback(button, pos); //attaches the button to the respective callback
gtk_grid_attach(GTK_GRID(grid2), button, j, i, 1, 1); //sets the defaults for creating each table button
if (pos ==0)
{
gtk_widget_set_size_request(button, 40, 40); //sets the size of the buttons
}
else 
{
gtk_widget_set_size_request(button, 40, 84); //sets the size of the buttons
}
buttoncontext = gtk_widget_get_style_context(button);
gtk_style_context_add_class(buttoncontext, "button_style");
gtk_style_context_add_provider (buttoncontext,GTK_STYLE_PROVIDER(Provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

pos++; //changes the position 
}
}

grid3 = gtk_grid_new();
pos = 0;
i = 0;
j = 0;

for (i=0; i < 1 ; i++) //for loop for the rows
{
for (j=0; j < 2; j++) //for loop for the columns
{
button = gtk_button_new_with_label(misc[pos]); //sets each button label to the respective button 
main2_callback(button, pos); //attaches the button to the respective callback
gtk_grid_attach(GTK_GRID(grid3), button, j, i, 1, 1); //sets the defaults for creating each table button
if (pos ==0)
{
gtk_widget_set_size_request(button, 83, 40); //sets the size of the buttons
}
else 
{
gtk_widget_set_size_request(button, 40, 40); //sets the size of the buttons
}
buttoncontext = gtk_widget_get_style_context(button);
gtk_style_context_add_class(buttoncontext, "button_style");
gtk_style_context_add_provider (buttoncontext,GTK_STYLE_PROVIDER(Provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

pos++; //changes the position 
}
}

grid4 = gtk_grid_new();
pos = 0;
i = 0;
j = 0;

for (i=0; i < 5 ; i++) //for loop for the rows
{
for (j=0; j < 2; j++) //for loop for the columns
{
button = gtk_button_new_with_label(secondarys2[pos]); //sets each button label to the respective button 
secondary2_callback(button, pos); //attaches the button to the respective callback
gtk_grid_attach(GTK_GRID(grid4), button, j, i, 1, 1); //sets the defaults for creating each table button
gtk_widget_set_size_request(button, 40, 40); //sets the size of the buttons
buttoncontext = gtk_widget_get_style_context(button);
gtk_style_context_add_class(buttoncontext, "button_style");
gtk_style_context_add_provider (buttoncontext,GTK_STYLE_PROVIDER(Provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
pos++; //changes the position 
}
}
gtk_grid_set_column_spacing(GTK_GRID(numberpad), 3);
gtk_grid_set_row_spacing(GTK_GRID(numberpad), 3);
gtk_grid_set_column_spacing(GTK_GRID(grid2), 3);
gtk_grid_set_row_spacing(GTK_GRID(grid2), 3);
gtk_grid_set_column_spacing(GTK_GRID(grid3), 3);
gtk_grid_set_row_spacing(GTK_GRID(grid3), 3);
gtk_grid_set_column_spacing(GTK_GRID(grid4), 3);
gtk_grid_set_row_spacing(GTK_GRID(grid4), 3);

conversionbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);

pos=0;

for (i=0; i < 4 ; i++) //for loop for the rows
{
  labels = gtk_check_button_new_with_label(conversions[i]);
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(labels), FALSE);
  conversion_callback(labels, pos);
  labelcontext = gtk_widget_get_style_context(labels);
  gtk_style_context_add_class(labelcontext, "label_style");
  gtk_style_context_add_provider (labelcontext,GTK_STYLE_PROVIDER(Provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
gtk_box_pack_start(GTK_BOX(conversionbox), labels, FALSE, FALSE, 0); //packs the display into the vbox

pos++; //changes the position 
}

gridbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
gridvbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);

vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1); //creates a vbox without autosizing 
gtk_container_add(GTK_CONTAINER(window), vbox); //adds the vbox to the window 
gtk_box_pack_start (GTK_BOX (vbox), menu_bar, FALSE, FALSE, 2);
gtk_box_pack_start(GTK_BOX(vbox), display, FALSE, FALSE, 0); //packs the display into the vbox
gtk_box_pack_start(GTK_BOX(vbox), conversionbox, FALSE, FALSE, 0); //packs the display into the vbox
gtk_box_pack_start(GTK_BOX(vbox), gridbox, FALSE, FALSE, 0); //packs the table into the vbox
gtk_box_pack_start(GTK_BOX(gridbox), gridvbox, FALSE, FALSE, 0); //packs the table into the vbox
gtk_box_pack_start(GTK_BOX(gridvbox), numberpad, FALSE, FALSE, 0); //packs the table into the vbox
gtk_box_pack_start(GTK_BOX(gridvbox), grid3, FALSE, FALSE, 3); //packs the table into the vbox
gtk_box_pack_start(GTK_BOX(gridbox), grid2, FALSE, FALSE, 2); //packs the table into the vbox
gtk_box_pack_start(GTK_BOX(gridbox), grid4, FALSE, FALSE, 5); //packs the table into the vbox

g_signal_connect(G_OBJECT(window), "destroy", //these lines are for the x at the top of the screen to close the window
  G_CALLBACK(gtk_main_quit), NULL);

gtk_widget_show_all(window); //shows all widgets 

gtk_main();//gtk main, this is the main loop of GTK

return 0;
}

gboolean keyboard_callback (GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
  switch (event->keyval) //full list of system keys here https://gitlab.gnome.org/GNOME/gtk/raw/master/gdk/gdkkeysyms.h
  {
    case GDK_KEY_KP_1:
    button1_callback();
    break;
    case GDK_KEY_KP_2:
    button2_callback();
    break;
    case GDK_KEY_KP_3:
    button3_callback();
    break;
    case GDK_KEY_KP_4:
    button4_callback();
    break;
    case GDK_KEY_KP_5:
    button5_callback();
    break;
    case GDK_KEY_KP_6:
    button6_callback();
    break;
    case GDK_KEY_KP_7:
    button7_callback();
    break;
    case GDK_KEY_KP_8:
    button8_callback();
    break;
    case GDK_KEY_KP_9:
    button9_callback();
    break;
    case GDK_KEY_KP_0:
    button0_callback();
    break;
    case GDK_KEY_KP_Add:
    add_callback();
    break;
    case GDK_KEY_KP_Subtract:
    subtract_callback();
    break;
    case GDK_KEY_KP_Multiply:
    multiply_callback();
    break;
    case GDK_KEY_KP_Divide:
    divide_callback();
    break;
    case GDK_KEY_KP_Enter:
    equals_callback();
    break;
  }
  return FALSE;
}

void main_callback(GtkWidget *button, guint data) //this function is just a switch for all of the button callbacks. 
{
  switch (data)
  {
    case 1:  g_signal_connect(button, "clicked", G_CALLBACK(divide_callback), NULL);
    break;
    case 2:  g_signal_connect(button, "clicked", G_CALLBACK(multiply_callback), NULL); 
    break;
    case 3:  g_signal_connect(button, "clicked", G_CALLBACK(button7_callback), NULL);
    break;
    case 4:  g_signal_connect(button, "clicked", G_CALLBACK(button8_callback), NULL);
    break;
    case 5:  g_signal_connect(button, "clicked", G_CALLBACK(button9_callback), NULL);
    break;
    case 6:  g_signal_connect(button, "clicked", G_CALLBACK(button4_callback ), NULL); 
    break;
    case 7:  g_signal_connect(button, "clicked", G_CALLBACK(button5_callback), NULL);
    break;
    case 8:  g_signal_connect(button, "clicked", G_CALLBACK(button6_callback), NULL);
    break;
    case 9:  g_signal_connect(button, "clicked", G_CALLBACK(button1_callback), NULL);
    break;
    case 10:  g_signal_connect(button, "clicked", G_CALLBACK(button2_callback), NULL); 
    break; 
    case 11:  g_signal_connect(button, "clicked", G_CALLBACK(button3_callback ), NULL); 
    break;
  }
}

void main2_callback(GtkWidget *button, guint data) //this function is just a switch for all of the button callbacks. 
{
  switch (data)
  {
    case 0:  g_signal_connect(button, "clicked", G_CALLBACK(button0_callback), NULL);
    break;
    case 1:  g_signal_connect(button, "clicked", G_CALLBACK(decimal_callback), NULL);
    break;
  }
}

void secondary_callback(GtkWidget *button, guint data) //this function is just a switch for all of the button callbacks. 
{
  switch (data)
  {
    case 0:  g_signal_connect(button, "clicked", G_CALLBACK(subtract_callback), NULL);
    break;
    case 1:  g_signal_connect(button, "clicked", G_CALLBACK(add_callback), NULL);
    break;
    case 2:  g_signal_connect(button, "clicked", G_CALLBACK(equals_callback), NULL);
    break;
  }
}
void secondary2_callback(GtkWidget *button, guint data) //this function is just a switch for all of the button callbacks. 
{
  switch (data)
  {
    case 0:  g_signal_connect(button, "clicked", G_CALLBACK(clear_callback), NULL);
    break;
    case 1: g_signal_connect(button, "clicked", G_CALLBACK(squared_callback), NULL);
    break;
    case 2: g_signal_connect(button, "clicked", G_CALLBACK(power_callback), NULL);
    break;
    case 3: g_signal_connect(button, "clicked", G_CALLBACK(squareroot_callback), NULL);
    break;
    case 5: g_signal_connect(button, "clicked", G_CALLBACK(factorial_callback), NULL);
    break;
  }
}

void conversion_callback(GtkWidget *label, guint data)
{
  switch (data)
  {
    case 0:g_signal_connect(label, "clicked", G_CALLBACK(decimalconvert), NULL);
    break;
    case 1:g_signal_connect(label, "clicked", G_CALLBACK(decimaltobinary), NULL);
    break;
    case 3:g_signal_connect(label, "clicked", G_CALLBACK(decimaltooct), NULL);
    break;
  }
}

void decimaltobinary () //this function converts decimal to binary using if input%2=1 then output one else output 0
{
int base = 2;
int i=0;
int holder[128];
int input = num1;
if (binarycount ==1)
{
char preview[128];
sprintf(preview,"%d", input); //copies num1 to the preview 
gtk_text_buffer_set_text (buffer, preview, -1); //displays num1 
binarycount=0;
}
else 
{
while( input >=1)
{
  if(input%base >=1)
  {
    input/=2;
    holder[i]=1;
  }
  else
  {
    input/=2;
    holder[i]=0;
  }
  i++;
}
for (int j=i-1, i=0; j>=0; j-- ,i++)
{

if(i==0)
{
input = holder[j];
}
else
{
input*=10;
input+=holder[j];
}
}
}
char preview[128];
sprintf(preview,"%d", input); //copies num1 to the preview 
gtk_text_buffer_set_text (buffer, preview, -1); //displays num1 
binarycount=1;
}

void decimaltooct () //this function converts decimal to binary using if input%2=1 then output one else output 0
{
int i=0;
int holder[128];
int input = num1;
if (octcount ==1)
{
char preview[128];
sprintf(preview,"%d", input); //copies num1 to the preview 
gtk_text_buffer_set_text (buffer, preview, -1); //displays num1 
octcount=0;
}
else 
{
while( input >0)
{
    holder[i]= input % 8;
    input/=8;
  i++;
}
for (int j=i-1, i=0; j>=0; j-- ,i++)
{

if(i==0)
{
input = holder[j];
}
else
{
input*=10;
input+=holder[j];
}
}
}
char preview[128];
sprintf(preview,"%d", input); //copies num1 to the preview 
gtk_text_buffer_set_text (buffer, preview, -1); //displays num1 
octcount=1;
}

void decimalconvert ()
{
char preview[32];
sprintf(preview,"%lf", num1); //copies num1 to the preview 
gtk_text_buffer_set_text (buffer, preview, -1); //displays num1 
}

int leftshift(double base) //shifts the numbers to the left to account for multiple input numbers 
{
  base=base*10;
  return base;
}

void button1_callback() //callback for number 1 
{
if(placementcount >0) //if the placement is higher than 0
{
num1=leftshift(num1); //shift the number placement 1 to the left
num1=num1+1; //add 1
placementcount++; //add 1 to the placement 
}
if ( placementcount == 0 && decimalcount ==0) //if this is the first number input
{
num1=1; //that number =1
placementcount++; //placement increases
}
else if(decimalcount != 0) //if you press the decimal button, it does 10^-1, 10^-2 etc
{
double holder = 0; //declares holder as type double
holder= pow(10, decimalcount);
num1+=holder;
decimalcount--;
}
char preview[17];
sprintf(preview, "%lf", num1); //copies the number to the preview variable 
gtk_text_buffer_set_text (buffer, preview, -1); //sends the preview to the display 
}
void button2_callback() //callback for number 2
{
if(placementcount >0) //if the placement is higher than 0
{
num1=leftshift(num1); //shift the bits to the left
num1=num1+2; //add 2
placementcount++; //increase placement 
}
if (placementcount == 0 && decimalcount ==0) //if first button to be pressed
{
num1=2; //that num =2
placementcount++; //increase placement 
}
else if(decimalcount <0) //if decimal pressed 
{
double holder = 0; //declares holder as type double
holder= pow(10, decimalcount)*2; //shifts to the right via 2(10^-1) 2(10^-2), etc 
num1+=holder; //adds it to number 1 
decimalcount--; //decreases the decimal placement 
}
char preview[17];
sprintf(preview, "%lf", num1); //sets num 1 to preview 
gtk_text_buffer_set_text (buffer, preview, -1); // displays preview 
}
void button3_callback () //callback for number 3 
{
if(placementcount >0) //if placement is over 0 
{
num1=leftshift(num1); //shifts placement of number to the left
num1=num1+3; //adds 3 
placementcount++; //increases placement 
}
else if(decimalcount <0) // if decimal pressed 
{
double holder = 0; //declares holder as type double
holder= pow(10, decimalcount)*3; //shifts bits to the right via 3(10^-1), 3(10^-2), etc
num1+=holder; //adds the number to num1 
decimalcount--;//decreases the decimal count 
}
else if (placementcount == 0 &&decimalcount ==0) //if first number
{
num1=3; //number equals 3
placementcount++; // increase placement 
}
char preview[17];
sprintf(preview, "%lf", num1); //sets preview to num1
gtk_text_buffer_set_text (buffer, preview, -1); //displays preview 
}
void button4_callback () //button 4 callback 
{
if(placementcount >0) //if placement is over 0
{
num1=leftshift(num1); //shifts bits to the left 
num1=num1+4; //adds 4
placementcount++; //increases placement 
}
else if(decimalcount <0) //if decimal is pressed
{
double holder = 0; //declares holder as type double
holder= pow(10, decimalcount)*4; //shifts number to the right 
num1+=holder; //adds to num1 
decimalcount--; //decreases decimal count 
}
else if (placementcount == 0 && decimalcount == 0) //if first button pressed 
{
num1=4; //num1 =4
placementcount++; //increases placement 
}
char preview[17];
sprintf(preview, "%lf", num1); //copies num1 to preview 
gtk_text_buffer_set_text (buffer, preview, -1); //displays preview 
}
void button5_callback() //callback for number 5
{
if(placementcount >0) //if placement is over 0
{
num1=leftshift(num1); //shifts number to the left 
num1=num1+5; //adds 5 
placementcount++; //increases placment 
}
else if(decimalcount <0) //if decimal is pressed 
{
double holder = 0; //declares holder as type double
holder= pow(10, decimalcount)*5; //shifts number to the right 
num1+=holder; //adds it to num1 
decimalcount--; //decreases decimal count 
}
else if (placementcount == 0 && decimalcount == 0) //if first button pressed 
{
num1=5; //num1 is 5 
placementcount++; //increases placement 
}
char preview[17];
sprintf(preview, "%lf", num1); //copies num1 to preview 
gtk_text_buffer_set_text (buffer, preview, -1); //displays preview 
}
void button6_callback() //callback function for button 6
{
if(placementcount >0) //if placement is over 0
{
num1=leftshift(num1); //left shift the number 
num1=num1+6; //add 6
placementcount++; //increase placement 
}
else if(decimalcount <0) //if decimal pressed 
{
double holder = 0; //declares holder as type double
holder= pow(10, decimalcount)*6; //right shift 
num1+=holder; //add to num1 
decimalcount--; //decrease decimal count 
}
else if (placementcount == 0 && decimalcount == 0) //if first button pressed 
{
num1=6; //num1 is 6 
placementcount++; //placement increases 
}
char preview[17];
sprintf(preview, "%lf", num1);//copies num1 to preview 
gtk_text_buffer_set_text (buffer, preview, -1); //diplays preview 
}
void button7_callback() //number 7 callback 
{
if(placementcount >0) //if placement is over 0
{
num1=leftshift(num1); //left shift the number 
num1=num1+7; //add 7
placementcount++; //increase placement 
}
else if(decimalcount <0) //if decimal pressed 
{
double holder = 0; //declares holder as type double
holder= pow(10, decimalcount)*7; //right shift the number 7 by the amount of decimals 
num1+=holder;  //add to num1 
decimalcount--; //decrease decimal count 
}
else if ( placementcount == 0 && decimalcount ==0) //if first button pressed 
{
num1=7; //num1 is 7
placementcount++; // increase placement 
}
char preview[17];
sprintf(preview, "%lf", num1); //copies num1 to preview 
gtk_text_buffer_set_text (buffer, preview, -1); //displays preview 
}
void button8_callback() //number 8 callback 
{
if(placementcount >0) //if placment is over 0
{
num1=leftshift(num1); //left shift the number 
num1=num1+8; //add 8
placementcount++; //increase placement 
}
else if(decimalcount <0) //if decimal pressed 
{
double holder = 0; //declares holder as type double
holder= pow(10, decimalcount)*8; //right shift 8 by the decimal number 
num1+=holder; //add to num1 
decimalcount--; //decrease decimal count 
}
else if (placementcount == 0 && decimalcount == 0) //if first button pressed 
{
num1=8; //num1 is 8 
placementcount++; //increase the placement 
}
char preview[17];
sprintf(preview, "%lf", num1); //copies num1 to preview 
gtk_text_buffer_set_text (buffer, preview, -1); //displays preview 
}
void button9_callback() //number 9 callback 
{
if(placementcount >0) // if placement is over 0
{
num1=leftshift(num1); //left shift num1 
num1=num1+9; //add 9
placementcount++; //increase placement 
}
else if(decimalcount <0) //if decimal pressed 
{
double holder = 0; //declares holder as type double
holder= pow(10, decimalcount)*9; //right shift 9 by the decimal count 
num1+=holder; // adds to num1 
decimalcount--; //decreases decimal count 
}
else if (placementcount == 0 && decimalcount ==0) //if first button pressed 
{
num1=9; //num is 9 
placementcount++; //increase placement 
}
char preview[17];
sprintf(preview, "%lf", num1); //copies placement to preview 
gtk_text_buffer_set_text (buffer, preview, -1); //displays preview 
}
void button0_callback() //button 0 callback 
{
if(placementcount >0) //if placement is over 0
{
num1*=10; //left shift the number 
}
else if (decimalcount <0) //if decimal pressed 
{
decimalcount--; //decrease decimal count 
}
else if (placementcount == 0 && decimalcount ==0) //if first number pressed 
{
num1=0; //num is 0
}
char preview[17];
sprintf(preview, "%lf", num1); //copies num1 to the preview 
gtk_text_buffer_set_text (buffer, preview, -1); //displays num1 
}
void multiply_callback() //* button, sets all secondarys to 0 except for multcount, makes num2=num1 so num1 can be reused
{
  multcount = 1;
  addcount = 0;
  subcount = 0;
  divcount = 0;
  placementcount = 0;
  decimalcount = 0;
  powercount = 0;
  squaredcount = 0;
  squareroot = 0;
  factorialcount = 0;
  num2 = num1;
}
void add_callback() //+ button, sets all secondarys to 0 except for addcount, makes num2=num1 so num1 can be reused
{
  multcount = 0;
  addcount = 1;
  subcount = 0;
  divcount = 0;
  placementcount = 0;
  decimalcount = 0;
  powercount = 0;
  squaredcount = 0;
  squareroot = 0;
  factorialcount = 0;
  num2 = num1;
}
void subtract_callback()//- button, sets all secondarys to 0 except for subcount, makes num2=num1 so num1 can be reused
{
  multcount = 0;
  addcount = 0;
  subcount = 1;
  divcount = 0;
  placementcount = 0;
  decimalcount = 0;
  powercount = 0;
  squaredcount = 0;
  squareroot = 0;
  factorialcount = 0;
  num2 = num1;
}
void divide_callback()// "/" button, sets all secondarys to 0 except for divcount, makes num2=num1 so num1 can be reused
{
  multcount = 0;
  addcount = 0;
  subcount = 0;
  divcount = 1;
  placementcount = 0;
  decimalcount = 0;
  powercount = 0;
  squaredcount = 0;
  squareroot = 0;
  factorialcount = 0;
  num2 = num1;
}
void squared_callback()
{
  multcount = 0;
  addcount = 0;
  subcount = 0;
  divcount = 0;
  placementcount = 0;
  decimalcount = 0;
  powercount = 0;
  squaredcount = 1;
  squareroot = 0;
  factorialcount = 0;
  equals_callback();
}
void power_callback() //* button, sets all secondarys to 0 except for multcount, makes num2=num1 so num1 can be reused
{
  multcount = 0;
  addcount = 0;
  subcount = 0;
  divcount = 0;
  placementcount = 0;
  decimalcount = 0;
  powercount = 1;
  squaredcount = 0;
  squareroot = 0;
  factorialcount = 0;
  num2 = num1;
}

void squareroot_callback()
{
  multcount = 0;
  addcount = 0;
  subcount = 0;
  divcount = 0;
  placementcount = 0;
  decimalcount = 0;
  powercount = 0;
  squaredcount = 0;
  squareroot = 1;
  factorialcount = 0;
  equals_callback();
}

void factorial_callback()
{
  multcount = 0;
  addcount = 0;
  subcount = 0;
  divcount = 0;
  placementcount = 0;
  decimalcount = 0;
  powercount = 0;
  squaredcount = 0;
  squareroot = 0;
  factorialcount = 1;
  equals_callback();
}

void equals_callback() // = callback 
{
char finaloutput[200]; // character array for the text
if (addcount > 0) //if + was pressed it does the calculations 
{
  num1 = num2 + num1;
}
if (subcount > 0) //if - was pressed it does the calculations 
{
  num1 = num2 - num1;
}
if (multcount > 0) //if * was pressed it does the calculations 
{
  num1 = num2 * num1;
}
if (divcount > 0) //if / was pressed it does the calculations 
{
  num1 = num2 / num1;
}
if (powercount >0)
{
  num1 = pow(num2, num1);
}
if (squaredcount > 0)
{
  num1 = (num1 * num1);
}
if (squareroot > 0)
{
  num1 = sqrt(num1);
}
if (factorialcount > 0)
{
  int holder=1;
  for(long int i=1; i<=num1; i++)
  {
    holder*=i;
  }
  num1=holder;
}
sprintf(finaloutput, "%lf", num1); //copies num1 to preview 
gtk_text_buffer_set_text (buffer, finaloutput, -1); //displays preview
//once preview is displayed it sets all secondarys and placements to 0 
multcount = 0; 
addcount = 0;
subcount = 0;
divcount = 0;
placementcount = 0;
decimalcount = 0;
powercount = 0;
squaredcount = 0;
squareroot = 0;
factorialcount = 0;
}
void clear_callback() //clears all secondarys, variables, and placements 
{
  num1=0;
  num2 = 0;
  multcount = 0;
  addcount = 0;
  subcount = 0;
  divcount = 0;
  placementcount = 0;
  decimalcount = 0;
  powercount = 0;
  squaredcount = 0;
  squareroot = 0;
  factorialcount = 0;
  char preview[20];
  sprintf(preview, "%lf", num1);
  gtk_text_buffer_set_text (buffer, preview, -1);
}
void decimal_callback() //decimal callback 
{
placementcount = 0; //sets placement to 0 
decimalcount--; //decreases decimal count so that you can use 10^-1 etc 
char preview[20];
sprintf(preview, "%lf", num1); //copies num1 to preview 
gtk_text_buffer_set_text (buffer, preview, -1); //displays preview 
}
