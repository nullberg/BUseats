// -------------------
//    main.c
// -------------------



// Links
// -----------
// getting setup with Glade and C:   https://prognotes.net/2016/03/gtk-3-c-code-hello-world-tutorial-using-glade-3/
// Menu dropdown:                    http://zetcode.com/gui/gtk2/menusandtoolbars/
// Menu dropdown in python:          https://developer.gnome.org/gnome-devel-demos/stable/menubutton.py.html.en


#include <gtk/gtk.h>
// #include <stdlib.h>



// Declarations
// ------------------------------ 

// GtkLabel pointers
GtkWidget  *lbl_query_string;
GtkWidget  *lbl_python_output;

// GtkDialog pointers
GtkWidget  *dialog_seats_result;

// GtkComboBox pointers
GtkWidget  *entry_semester;
GtkWidget  *entry_year;
GtkWidget  *entry_college;

// GtkEntry pointers
GtkWidget  *entry_department;
GtkWidget  *entry_course_num;
GtkWidget  *entry_section_num;

// ------------------------------ 


 
int main( int argc,  char *argv[] )
{

    GtkBuilder  *builder; 
    GtkWidget   *window;

 
    gtk_init( &argc,  &argv );
    builder = gtk_builder_new();
    gtk_builder_add_from_file( builder,  "glade/window_main.glade",  NULL );
    window = GTK_WIDGET( gtk_builder_get_object( builder,  "window_main" ) );
    gtk_builder_connect_signals( builder,  NULL );


    // -------------------------------------------
    dialog_seats_result = GTK_WIDGET( gtk_builder_get_object(builder, "dialog_seats_result") );

    entry_semester = GTK_WIDGET( gtk_builder_get_object(builder, "entry_semester") );
    entry_year = GTK_WIDGET( gtk_builder_get_object(builder, "entry_year") );
    entry_college = GTK_WIDGET( gtk_builder_get_object(builder, "entry_college") );
    entry_department = GTK_WIDGET( gtk_builder_get_object(builder, "entry_department") );

    entry_course_num = GTK_WIDGET( gtk_builder_get_object(builder, "entry_course_num") );
    entry_section_num = GTK_WIDGET( gtk_builder_get_object(builder, "entry_section_num") );

    lbl_query_string = GTK_WIDGET( gtk_builder_get_object(builder, "lbl_query_string") );
    lbl_python_output = GTK_WIDGET( gtk_builder_get_object(builder, "lbl_python_output") );
    // -------------------------------------------


    g_object_unref(builder);
    gtk_widget_show(window);
    gtk_main();
 
    return 0;
}


// Returns a string of the inputs
const char *getMasterString()
{

    static char my_master_string[50] = "";

    const gchar *semester;
    const gchar *year;
    const gchar *college;
    const gchar *department;
    const gchar *course_num;
    const gchar *section_num;

    semester     =  gtk_entry_get_text( GTK_ENTRY(entry_semester) );
    year         =  gtk_entry_get_text( GTK_ENTRY(entry_year) );
    college      =  gtk_entry_get_text( GTK_ENTRY(entry_college) );
    department   =  gtk_entry_get_text( GTK_ENTRY(entry_department) );
    course_num   =  gtk_entry_get_text( GTK_ENTRY(entry_course_num) );
    section_num  =  gtk_entry_get_text( GTK_ENTRY(entry_section_num) );

    strcpy(my_master_string,""); // Must reset it first

    strcat(my_master_string,semester);
    strcat(my_master_string," ");
    strcat(my_master_string,year);
    strcat(my_master_string," ");
    strcat(my_master_string,college);
    strcat(my_master_string," ");
    strcat(my_master_string,department);
    strcat(my_master_string," ");
    strcat(my_master_string,course_num);
    strcat(my_master_string," ");
    strcat(my_master_string,section_num);

    return my_master_string;
}

// called when button "Check seats" is clicked
void on_btn_check_seats_clicked()
{

    char master_string[50] = "";
    strcpy( master_string, getMasterString() );
    gtk_label_set_text( GTK_LABEL(lbl_query_string), master_string );


    char seats_output[50] = "";
    char python_command[150] = "/home/omega/SW_projects/GTK_projects/using_Glade/bu-seats/python/check_BU_seats ";

    strcat(python_command, master_string);

    system(python_command);
    printf("%s\n",python_command);

    char num_from_file[100];
    FILE *file;
    file = fopen("/home/omega/SW_projects/GTK_projects/using_Glade/bu-seats/python/RESULT.txt","r");
    while(fgets(num_from_file, sizeof(num_from_file), file)!=NULL)
    printf("Data read=%s\n",num_from_file);
    fclose(file);

    strcpy( seats_output, num_from_file );

    gtk_label_set_text( GTK_LABEL( lbl_python_output), seats_output );


    // doc:  https://developer.gnome.org/gtk3/stable/GtkDialog.html
    //--------------------------------
    gint result = gtk_dialog_run( GTK_DIALOG(dialog_seats_result) );
    switch (result)
    {
       case GTK_RESPONSE_ACCEPT:
          // do_application_specific_something ();
          break;
       default:
          // do_nothing_since_dialog_was_cancelled ();
          break;
    }

    //--------------------------------

}

void on_btn_OK_clicked()
{
    // gtk_widget_destroy(dialog_seats_result);
    gtk_widget_hide(dialog_seats_result);
    
}



/*
void seats_result_dialog()
{
  GtkWidget *gtk_dialog_new();
}
*/
/*
void seats_result_dialog(GtkWindow *parent, gchar *message)

{

 GtkWidget *dialog, *label, *content_area;
 GtkDialogFlags flags;

 // Create the widgets
 flags = GTK_DIALOG_DESTROY_WITH_PARENT;
 dialog = gtk_dialog_new_with_buttons ("Message",
                                       parent,
                                       flags,
                                       _("_OK"),
                                       GTK_RESPONSE_NONE,
                                       NULL);

 content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
 label = gtk_label_new (message);

 // Ensure that the dialog box is destroyed when the user responds
 g_signal_connect_swapped (dialog,
                           "response",
                           G_CALLBACK (gtk_widget_destroy),
                           dialog);

 // Add the label, and show everything we’ve added
 gtk_container_add (GTK_CONTAINER (content_area), label);
 gtk_widget_show_all (dialog);
}
*/

 
// called when window is closed
void on_window_main_destroy()
{
    gtk_widget_destroy(dialog_seats_result);
    gtk_main_quit();
}





// Misc info
// ----------------

// ./check_BU_seats 2019 Fall CFA MP 600 A1
// system("/home/omega/SW_projects/GTK_projects/using_Glade/bu-seats/python/check_BU_seats '2019' 'Fall' 'CFA' 'MP' '600' 'A1'");
// system(strcat("/home/omega/SW_projects/GTK_projects/using_Glade/bu-seats/python/check_BU_seats ",master_string));

// EXAMPLE of having count label lbl_count:
// char str_count[30] = {0};
// static unsigned int count = 0;
// count++;
// sprintf(str_count, "counter: %d", count);
// gtk_label_set_text( GTK_LABEL(lbl_count),  str_count );
