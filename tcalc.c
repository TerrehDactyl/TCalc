#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <math.h>
#define arraysize(x)  (sizeof(x) / sizeof((x)[0]))
//compile with gcc -Wall -g -lm calc.c -o calc `pkg-config --cflags --libs gtk+-3.0`
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
void clear_input();
void decimal_callback();
void power_callback();
void squared_callback();
void squareroot_callback();
void secondary_callback(GtkWidget *button, guint data);
void main_callback(GtkWidget *fixed, guint data);
void main2_callback(GtkWidget *button, guint data);
void secondary2_callback(GtkWidget *button, guint data);
void modulo();
void decimalconverter();
void octconverter();
void binaryconverter();
void hexconverter();
void percent_callback();
void factorial_callback();
void attach_conversion_callback(GtkWidget *label, void *conversion_callback_arr);
gboolean keyboard_callback (GtkWidget *widget, GdkEventKey *event, gpointer user_data);
void clear_count();
void button_connect_callback(GtkWidget *button, void *button_callback);
void add_context(const gchar *style, GtkWidget *widget);
void set_spacing(GtkWidget *widget, int colspace, int rowspace);
void createmenu(GtkWidget *root_menu, const gchar *style[], gchar *menu_array[], int arraylen, void *callback[]);
void createsinglesizegrid(GtkWidget *grid, gchar *labels[], void *callback[], int rows, int columns, const gchar *style[], int stylenumber);
void createtwosizegrid(GtkWidget *grid, gchar *labels[], void  *callback[], int rows, int columns,  int normwidth, int normlen, int specwidth, int speclen, int range, const gchar *style[], int stylenumber);
void preview();
void doesallthework(int ButtonNumber);
void undo();
void redo();
void copy();
void cut();
void menu_callback(GtkWidget *menu_items, void *callback);
void nullcallback();
void pi();
void phi();
void euler();

struct counting_variables
{
  int mult, add, sub, div, placement, decimal, percent, power, squared, squareroot, factorial, mod, hist, undo;
}count;

struct input_variables
{
  long double num1, num2;
  long double history[128];
  char preview[20];
}input;

struct Global_Widgets
{
GtkWidget *display; //widget for the display 
GtkTextBuffer *buffer; //widget for the text 
}gwidget;

int main(int argc, char *argv[])  //gotta start somewhere
{
GtkWidget *window; //widget for the window
GtkWidget *left_keypad, *right_keypad, *bottom_keypad, *adv_operator_keypad;
GtkWidget *gridhbox;
GtkWidget *gridvbox;
GtkWidget *vbox; //widget for the vertical box
GtkWidget *labels;
GtkWidget *conversionbox;
GtkWidget *decimalbutton;
GtkWidget *menu_bar;
GtkWidget *root_menu;
gchar *left_keypad_labels[] = {"%", "/", "*", "7", "8", "9","4", "5", "6","1", "2", "3"}; //labels for the buttons 
gchar *bottom_keypad_labels[] = {"0", "."};
gchar *right_keypad_labels[] = {"-", "+", "="};
gchar *adv_operator_labels[] = {"CE", "x2", "^", "sqrt", "Mod", "x!", "Undo", "Redo"};
gchar *conversions[] = {"Dec", "Bin", "Hex", "Oct"};
gchar *headers [] = {"File", "Edit", "Constants", "Settings", "Help"};
gchar *file_menu [] = {"Quit"};
gchar *edit_menu [] = {"Undo", "Redo", "Cut", "Copy"};
gchar *constants_menu [] = {"Pi", "Euler Number", "Golden Ratio"};
const gchar *style [] = {"menu_style", "display_style", "window_style", "button_style", "label_style", "menu_style", "operators_style"};
size_t file_len = arraysize(file_menu);
size_t edit_len = arraysize(edit_menu);
size_t constants_len = arraysize(constants_menu);
void *left_keypad_callback[] = {percent_callback, divide_callback, multiply_callback, button7_callback, button8_callback, button9_callback,
  button4_callback, button5_callback, button6_callback, button1_callback, button2_callback, button3_callback};
void *bottom_keypad_callback[] = {button0_callback, decimal_callback};
void *right_keypad_callback[] = {subtract_callback, add_callback, equals_callback};
void *adv_operator_keypad_callback[] = {clear_input, squared_callback, power_callback, squareroot_callback, modulo,factorial_callback, undo, redo};
void *conversion_callback_arr[] = {decimalconverter, binaryconverter, hexconverter, octconverter};
void *edit_callback[] = {undo, redo, cut, copy};
void *file_callback[] = {gtk_main_quit};
void *constants_callback[] = {pi, euler, phi};

gtk_init(&argc, &argv); //starting gtk 

window = gtk_window_new(GTK_WINDOW_TOPLEVEL); //creates toplevel window
gtk_window_set_title(GTK_WINDOW(window), "TCalc v.1.0"); //sets a window title 
gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER); //opens the window in the center of the screen
gtk_container_set_border_width(GTK_CONTAINER(window), 5); //sets the border size of the window
g_signal_connect(window, "key-release-event", G_CALLBACK(keyboard_callback), NULL);

menu_bar = gtk_menu_bar_new ();
char buf[128];
for (int i = 0; i < 5; i++)
{
  sprintf (buf, "%s", headers[i]);
  root_menu = gtk_menu_item_new_with_label (buf);

  switch (i)
  {
    case 0: createmenu(root_menu, style, file_menu, file_len, file_callback);
    break;
    case 1: createmenu(root_menu, style, edit_menu, edit_len, edit_callback);
    break;
    case 2: createmenu(root_menu, style, constants_menu, constants_len, constants_callback);
  }
  gtk_menu_shell_append (GTK_MENU_SHELL (menu_bar), root_menu);
  add_context(style[0], root_menu);
}

gwidget.display = gtk_text_view_new (); //sets the display widget as a text display 
gwidget.buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW ( gwidget.display)); //sets the gwidget.buffer widget to the text gwidget.buffer of display
gtk_widget_set_size_request( gwidget.display, 150, 40); //sets the size of the display 
gtk_widget_add_events(window, GDK_KEY_PRESS_MASK);

left_keypad= gtk_grid_new(); //sets the table widget as a 4x4 arrangement without autosizing
createsinglesizegrid(left_keypad, left_keypad_labels, left_keypad_callback, 4, 3, style, 6);
set_spacing(left_keypad, 3, 3);

right_keypad = gtk_grid_new();
createtwosizegrid(right_keypad, right_keypad_labels, right_keypad_callback, 3, 1, 40, 84, 40, 40, 0, style, 6);
set_spacing(right_keypad, 3, 3);

bottom_keypad = gtk_grid_new();
createtwosizegrid(bottom_keypad, bottom_keypad_labels, bottom_keypad_callback, 1, 2, 40, 40, 83, 40, 0, style, 6);
set_spacing(bottom_keypad, 3, 3);

adv_operator_keypad = gtk_grid_new();
createsinglesizegrid(adv_operator_keypad, adv_operator_labels, adv_operator_keypad_callback, 4, 2, style, 6);
set_spacing(adv_operator_keypad, 3, 3);

add_context(style[1],  gwidget.display);
add_context(style[2], window);
add_context(style[2], menu_bar);

conversionbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);

decimalbutton = gtk_radio_button_new_with_label(NULL, conversions[0]);
attach_conversion_callback(decimalbutton, conversion_callback_arr[0]);
add_context(style[4], decimalbutton);
gtk_box_pack_start(GTK_BOX(conversionbox), decimalbutton, FALSE, FALSE, 0); //packs the display into the vbox

for (int i=1; i < arraysize(conversions); i++) //for loop for the rows
{
  labels = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(decimalbutton), conversions[i]);
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(labels), FALSE);
  attach_conversion_callback(labels, conversion_callback_arr[i]);
  add_context(style[4], labels);
gtk_box_pack_start(GTK_BOX(conversionbox), labels, FALSE, FALSE, 0); //packs the display into the vbox
}
gridhbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
gridvbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);

vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1); //creates a vbox without autosizing 

gtk_container_add(GTK_CONTAINER(window), vbox); //adds the vbox to the window 
gtk_box_pack_start (GTK_BOX (vbox), menu_bar, FALSE, FALSE, 2);
gtk_box_pack_start(GTK_BOX(vbox),  gwidget.display, FALSE, FALSE, 0); //packs the display into the vbox
gtk_box_pack_start(GTK_BOX(vbox), conversionbox, FALSE, FALSE, 0); //packs the display into the vbox
gtk_box_pack_start(GTK_BOX(vbox), gridhbox, FALSE, FALSE, 0); //packs the table into the vbox
gtk_box_pack_start(GTK_BOX(gridhbox), gridvbox, FALSE, FALSE, 0); //packs the table into the vbox
gtk_box_pack_start(GTK_BOX(gridvbox), left_keypad, FALSE, FALSE, 0); //packs the table into the vbox
gtk_box_pack_start(GTK_BOX(gridvbox), bottom_keypad, FALSE, FALSE, 3); //packs the table into the vbox
gtk_box_pack_start(GTK_BOX(gridhbox), right_keypad, FALSE, FALSE, 2); //packs the table into the vbox
gtk_box_pack_start(GTK_BOX(gridhbox), adv_operator_keypad, FALSE, FALSE, 5); //packs the table into the vbox

g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

gtk_widget_show_all(window); //shows all widgets 

gtk_main();//gtk main, this is the main loop of GTK

return 0;
}

void nullcallback(){}

void createtwosizegrid(GtkWidget *grid, gchar *labels[], void  *callback[], int rows, int columns,  int normwidth, int normlen, int specwidth, int speclen, int range, const gchar *style[], int stylenumber)
{
  GtkWidget *button;
  int pos = 0;
for (int i=0; i < rows ; i++) //for loop for the rows
{
for (int j=0; j < columns; j++) //for loop for the columns
{ 
button = gtk_button_new_with_label(labels[pos]); //sets each button label to the respective button 
button_connect_callback(button, callback[pos]); //attaches the button to the respective callback
gtk_grid_attach(GTK_GRID(grid), button, j, i, 1, 1); //sets the defaults for creating each table button
if (pos <= range)
{
gtk_widget_set_size_request(button, specwidth, speclen); //sets the size of the buttons
}
else 
{
gtk_widget_set_size_request(button, normwidth, normlen); //sets the size of the buttons
}
add_context(style[stylenumber], button);
pos++;
}
}
}

void set_spacing(GtkWidget *widget, int colspace, int rowspace)
{
  gtk_grid_set_column_spacing(GTK_GRID(widget), colspace);
  gtk_grid_set_row_spacing(GTK_GRID(widget), rowspace);
}

void add_context(const gchar *style, GtkWidget *widget)
{
  GtkCssProvider* Provider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(GTK_CSS_PROVIDER(Provider), "Styles.css", NULL);
  GtkStyleContext *context = gtk_widget_get_style_context(widget);
  gtk_style_context_add_class(context, style);
  gtk_style_context_add_provider (context,GTK_STYLE_PROVIDER(Provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
}

void createsinglesizegrid(GtkWidget *grid, gchar *labels[], void *callback[], int rows, int columns, const gchar *style[], int stylenumber)
{
  int pos = 0;
GtkWidget *button; //widget for the buttons 
for (int i=0; i < rows; i++) //for loop for the rows
{
for (int j=0; j < columns; j++) //for loop for the columns
{
button = gtk_button_new_with_label(labels[pos]); //sets each button label to the respective button 
button_connect_callback(button, callback[pos]); //attaches the button to the respective callback
gtk_grid_attach(GTK_GRID(grid), button, j, i, 1, 1); //sets the defaults for creating each table button
gtk_widget_set_size_request(button, 40, 40); //sets the size of the buttons
add_context(style[stylenumber], button);
pos++; //changes the position 
}
}
}

void button_connect_callback(GtkWidget *button, void *button_callback)
{
  g_signal_connect(button, "clicked", G_CALLBACK(button_callback), NULL);
}

void createmenu(GtkWidget *root_menu, const gchar *style[], gchar *menu_array[], int arraylen, void *callback[])
{
  GtkWidget *menu;
  GtkWidget *menu_items;
  char buf[128];
  menu = gtk_menu_new();
  add_context(style[5], menu);
  for(int j = 0; j<arraylen; j++)
  {
    sprintf (buf, "%s", menu_array[j]);
    menu_items = gtk_menu_item_new_with_label(buf);
    menu_callback(menu_items, callback[j]);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_items);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(root_menu), menu);
  }
}

void menu_callback(GtkWidget *menu_items, void *callback)
{
  g_signal_connect_swapped(menu_items, "activate", G_CALLBACK(callback), NULL);
}

void attach_conversion_callback(GtkWidget *label, void *conversion_callback)
{
  g_signal_connect(label, "clicked", G_CALLBACK(conversion_callback), NULL);
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
  case GDK_KEY_KP_Decimal:
  decimal_callback();
  break;
  case GDK_KEY_percent:
  percent_callback();
  break;
}
return FALSE;
}

void binaryconverter () //this function converts decimal to binary using if output%2=1 then output one else output 0
{
  int base = 2;
  int i=0;
  char preview[128];
  long int output = input.num1;

  while( output >=1)
  {
    if(output%base >=1)
    {
      output/=2;
      preview[i]=1;
    }
    else
    {
      output/=2;
      preview[i]=0;
    }
    i++;
  }
  for (int j=i-1, i=0; j>=0; j-- ,i++)
  {

    if(i==0)
    {
      output = preview[j];
    }
    else
    {
      output*=10;
      output+=preview[j];
    }
  }
sprintf(preview,"%ld", output); //copies input.num1 to the preview 
gtk_text_buffer_set_text ( gwidget.buffer, preview, -1); //displays input.num1 
}

void hexconverter()
{
  long int temp;
  int i;
  char hexadecimalinput[16];
  char preview[128];
  long int decimalNumber = input.num1;

  for (i=0; decimalNumber!=0; i++) 
  {
    temp = decimalNumber % 16;
//To convert integer into character
    if( temp < 10)
    {
      temp =temp + 48; 
    }
    else
    {
      temp = temp + 55;
    }
    hexadecimalinput[i] = temp;
    decimalNumber = decimalNumber / 16;
  }
  for (int j=i-1, i=0; j>=0; j--)
  {
    preview[j] = hexadecimalinput[i];
    i++;
  }
gtk_text_buffer_set_text ( gwidget.buffer, preview, -1); //displays input.num1 
}

void octconverter () //this function converts decimal to binary using if output%2=1 then output one else output 0
{
  int i=0;
  int output = input.num1;
  char preview[128];

  while( output >0)
  {
    preview[i]= output % 8;
    output/=8;
    i++;
  }
  for (int j=i-1, i=0; j>=0; j-- ,i++)
  {

    if(i==0)
    {
      output = preview[j];
    }
    else
    {
      output*=10;
      output+=preview[j];
    }
  }
sprintf(preview,"%d", output); //copies input.num1 to the preview 
gtk_text_buffer_set_text ( gwidget.buffer, preview, -1); //displays input.num1 
}

void decimalconverter ()
{
  preview();
}

int leftshift(double base) //shifts the numbers to the left to account for multiple output numbers 
{
  base=base*10;
  return base;
}
void doesallthework(int ButtonNumber) //callback for number 1 
{
if( count.placement >0) //if the placement is higher than 0
{
input.num1=leftshift(input.num1); //shift the number placement 1 to the left
input.num1=input.num1+ButtonNumber; //add 1
count.placement++; //add 1 to the placement 
}
if (  count.placement == 0 &&  count.decimal ==0) //if this is the first number input
{
input.num1=ButtonNumber; //that number =1
count.placement++; //placement increases
}
else if( count.decimal != 0) //if you press the decimal button, it does 10^-1, 10^-2 etc
{
  double holder = pow(10,  count.decimal)*ButtonNumber;
  input.num1+=holder;
  count.decimal--;
}
input.history[count.hist] = input.num1;
count.hist++;
preview();
}

void button1_callback() //callback for number 1 
{
  doesallthework(1);
}

void button2_callback() //callback for number 2
{
  doesallthework(2);
}

void button3_callback () //callback for number 3 
{
  doesallthework(3);
}

void button4_callback () //button 4 callback 
{
  doesallthework(4);
}

void button5_callback() //callback for number 5
{
  doesallthework(5);
}

void button6_callback() //callback function for button 6
{
  doesallthework(6);
}

void button7_callback() //number 7 callback 
{
  doesallthework(7);
}

void button8_callback() //number 8 callback 
{
  doesallthework(8);
}

void button9_callback() //number 9 callback 
{
  doesallthework(9);
}

void button0_callback() //button 0 callback 
{
if( count.placement >0) //if placement is over 0
{
input.num1*=10; //left shift the number 
}
else if ( count.decimal <0) //if decimal pressed 
{
count.decimal--; //decrease decimal count 
}
else if ( count.placement == 0 &&  count.decimal ==0) //if first number pressed 
{
input.num1=0; //num is 0
}
preview();
}

void multiply_callback() //* button, sets all bottom_keypad_labels to 0 except for  count.mult, makes input.num2=input.num1 so input.num1 can be reused
{
  clear_count();
  count.mult = 1;
  input.num2 = input.num1;
}

void add_callback() //+ button, sets all bottom_keypad_labels to 0 except for  count.add, makes input.num2=input.num1 so input.num1 can be reused
{
  clear_count();
  count.add = 1;
  input.num2 = input.num1;
}

void subtract_callback()//- button, sets all bottom_keypad_labels to 0 except for  count.sub, makes input.num2=input.num1 so input.num1 can be reused
{
  clear_count();
  count.sub = 1;
  input.num2 = input.num1;
}

void divide_callback()// "/" button, sets all bottom_keypad_labels to 0 except for  count.div, makes input.num2=input.num1 so input.num1 can be reused
{
  clear_count();
  count.div = 1;
  input.num2 = input.num1;
}

void squared_callback()
{
  clear_count();
  count.squared = 1;
  equals_callback();
}

void power_callback() //* button, sets all bottom_keypad_labels to 0 except for  count.mult, makes input.num2=input.num1 so input.num1 can be reused
{
  clear_count();
  count.power = 1;
  input.num2 = input.num1;
}

void percent_callback() 
{
  clear_count();
  count.percent = 1;
  input.num2 = input.num1;
}

void squareroot_callback()
{
  clear_count();
  count.squareroot = 1;
  equals_callback();
}

void factorial_callback()
{
  clear_count();
  count.factorial = 1;
  equals_callback();
}

void modulo()
{
  clear_count();
  count.mod = 1;
  input.num2 = input.num1;
}

void equals_callback() // = callback 
{
if ( count.add > 0) //if + was pressed it does the calculations 
{
  input.num1 = input.num2 + input.num1;
}
if ( count.sub > 0) //if - was pressed it does the calculations 
{
  input.num1 = input.num2 - input.num1;
}
if ( count.mult > 0) //if * was pressed it does the calculations 
{
  input.num1 = input.num2 * input.num1;
}
if ( count.div > 0) //if / was pressed it does the calculations 
{
  input.num1 = input.num2 / input.num1;
}
if ( count.power >0)
{
  input.num1 = pow(input.num2, input.num1);
}
if ( count.squared > 0)
{
  input.num1 = (input.num1 * input.num1);
}
if ( count.squareroot > 0)
{
  input.num1 = sqrt(input.num1);
}
if ( count.factorial > 0)
{
  int output=1;
  for(long int i=1; i<=input.num1; i++)
  {
    output*=i;
  }
  input.num1=output;
}
if ( count.percent >0)
{
  input.num2 /= 100;
  input.num1 *= input.num2;
}
if ( count.mod > 0)
{
  int num1 = input.num1, num2 = input.num2;
  num1 = num2%num1;
  input.num1 = num1;
}
preview();
clear_count();//once preview is displayed it sets all bottom_keypad_labels and placements to 0 
}

void clear_input() //clears all bottom_keypad_labels, variables, and placements 
{
  clear_count();
  input.num1 = 0;
  input.num2 = 0;
  preview();
}

void decimal_callback() //decimal callback 
{
count.placement = 0; //sets placement to 0 
count.decimal--; //decreases decimal count so that you can use 10^-1 etc 
preview();
}

void preview()
{
sprintf(input.preview, "%Lf", input.num1); //copies input.num1 to preview 
gtk_text_buffer_set_text ( gwidget.buffer, input.preview, -1); //displays preview 
}

void clear_count()
{
  count.mult = 0;
  count.add = 0;
  count.sub = 0;
  count.div = 0;
  count.placement = 0;
  count.decimal = 0;
  count.power = 0;
  count.squared = 0;
  count.squareroot = 0;
  count.factorial = 0;
  count.percent = 0;
  count.hist = 0;
}

void undo()
{
  count.hist--;
  input.num1 = input.history[count.hist];
  count.hist++;
  preview();
}

void redo()
{
  input.num1 = input.history[count.hist];
  count.hist++;
  clear_count();
  preview();
}

void copy()
{
  GtkClipboard *clipboard= gtk_clipboard_get(GDK_SELECTION_CLIPBOARD); 
  gtk_clipboard_set_text(clipboard, input.preview, -1);
}

void cut()
{
  GtkClipboard *clipboard= gtk_clipboard_get(GDK_SELECTION_CLIPBOARD); 
  gtk_clipboard_set_text(clipboard, input.preview, -1);
  clear_input();
}

void pi()
{
  input.num1 = M_PI;
  input.history[count.hist] = input.num1;
  count.hist++;
  preview();
}

void phi()
{
  input.num1 = 1.61803398875;
  input.history[count.hist] = input.num1;
  count.hist++;
  preview();
}

void euler()
{
  input.num1 = 2.71828182846;
  input.history[count.hist] = input.num1;
  count.hist++;
  preview();
}
