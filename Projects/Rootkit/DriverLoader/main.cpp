#include <gtk/gtk.h>
#include <windows.h>
#include <Shlwapi.h>
#include "headders/native.h"

#define ZWLOADMODE							10
#define NTLOADMODE							20
#define SMLOADMODE							30

#include "headders/injection.h"

#define PACKAGE_VERSION "2.0"  
 
static void destroy( GtkWidget *widget, gpointer   data ); // exit main application
void About_DLoad (); // show about information
int Load_Driver(); // load driver the way we want
bool NtFunctionsInit(); // initialize native functions
BOOL RunDriverWithServiceManager(char *ServiceName, char *DriverPath);
BOOL RemoveDriverWithServiceManager(char *ServiceName, char *DriverPath);
BOOL RegDelnodeRecurse (HKEY hKeyRoot, LPTSTR lpSubKey);
BOOL MyDeleteKey (HKEY hKeyRoot, LPTSTR lpSubKey);
 
GtkWidget *picker;
GtkWidget *zwset_check_button, *ntload_check_button, *servmanag_check_button, *use_injection_check_button;
GtkWidget *drv_unload_check_button, *drv_delete_check_button, *drv_regent_delete_check_button;
GtkWidget *targ_proc_entry, *target_process_label, *injection_method_box;

//==================== do some setup stuff =====================//
int SetUpZwOption(){
    gtk_widget_set_sensitive(drv_unload_check_button, FALSE);
    gtk_widget_set_sensitive(drv_delete_check_button, FALSE);
    gtk_widget_set_sensitive(drv_regent_delete_check_button, FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(drv_unload_check_button), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(drv_delete_check_button), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(drv_regent_delete_check_button), FALSE);
return 0;   
}

int SetUpScOption(){
    gtk_widget_set_sensitive(drv_unload_check_button, TRUE);
    gtk_widget_set_sensitive(drv_delete_check_button, TRUE);
    gtk_widget_set_sensitive(drv_regent_delete_check_button, FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(drv_unload_check_button), TRUE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(drv_delete_check_button), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(drv_regent_delete_check_button), FALSE);
return 0;
}

int SetUpNtOption(){
    gtk_widget_set_sensitive(drv_unload_check_button, TRUE);
    gtk_widget_set_sensitive(drv_delete_check_button, TRUE);
    gtk_widget_set_sensitive(drv_regent_delete_check_button, TRUE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(drv_unload_check_button), TRUE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(drv_delete_check_button), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(drv_regent_delete_check_button), TRUE);
return 0;
}

int SetUpInjectionOption(){
    bool our_state;
    our_state = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(use_injection_check_button));
    if(our_state){
    gtk_widget_set_sensitive(target_process_label, TRUE);
    gtk_widget_set_sensitive(targ_proc_entry, TRUE);
    gtk_widget_set_sensitive(injection_method_box, TRUE);
    } else {
    gtk_widget_set_sensitive(target_process_label, FALSE);
    gtk_widget_set_sensitive(targ_proc_entry, FALSE);      
    gtk_widget_set_sensitive(injection_method_box, FALSE);     
    }
return 0;    
}

//====================== ###################### =====================//
 
int main( int   argc, char *argv[] ){
    GtkWidget *window, *description_label, *driver_label, *method_label, *exit_action_label, *os_version_label, 
              *os_version_label_ex, *nt_functions_label, *nt_functions_label_ex;
    GtkWidget *main_box, *button_box, *load_box, *method_box, *exit_action_box , *injection_box;
    GtkWidget *load_button, *about_button, *quit_button;
    GtkWidget *dialog, *methods_box, *exit_actions_box, *os_version_box, *nt_functions_box;
    char *filename; char container[256]; char nt_functions_container[1024];
    GtkWidget *sep1, *sep2, *sep3, *sep4, *sep5, *sep6, *sep7;
    OSVERSIONINFO VersionInfo;
    GtkTooltips *button_bar_tips;
    GtkWidget *use_injection_label;
    GtkWidget *HeaderBox, *frame, *gen_test_drv;
    
    gtk_init (&argc, &argv);
    	if(!NtFunctionsInit())MessageBoxA(0, "Not all native functions loaded!\n\This may cause application crash!", "WARNING", MB_ICONWARNING);
    
    memset(&VersionInfo, 0, sizeof(VersionInfo));
    RtlZeroMemory(container, sizeof(container));
    RtlZeroMemory(nt_functions_container, sizeof(nt_functions_container));
    VersionInfo.dwOSVersionInfoSize = sizeof(VersionInfo);
    button_bar_tips = gtk_tooltips_new ();
    
    HeaderBox = gtk_hbox_new(0,0);
    injection_method_box = gtk_hbox_new(0,0);
    
    
    zwset_check_button = gtk_radio_button_new_with_mnemonic (NULL, "_via ZwSetSystemInformation");
    ntload_check_button = gtk_radio_button_new_with_mnemonic_from_widget (GTK_RADIO_BUTTON (zwset_check_button), "_via NtLoadDriver");
    servmanag_check_button = gtk_radio_button_new_with_mnemonic_from_widget (GTK_RADIO_BUTTON (zwset_check_button), "_via Service Control Manager");
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ntload_check_button), TRUE);
    
    drv_unload_check_button = gtk_check_button_new_with_mnemonic ("_Unload Driver");
    drv_delete_check_button = gtk_check_button_new_with_mnemonic ("_Delete Driver");
    drv_regent_delete_check_button = gtk_check_button_new_with_mnemonic ("_Delete Driver Registry Entry");
    use_injection_check_button = gtk_check_button_new_with_mnemonic("_Yes");
    inject_with_rtl_check_box = gtk_radio_button_new_with_mnemonic (NULL, "_RtlCreateUserThread");
    inject_with_crt_check_box = gtk_radio_button_new_with_mnemonic_from_widget (GTK_RADIO_BUTTON (inject_with_rtl_check_box), "_CreateRemoteThread");
    
    gtk_box_pack_start( GTK_BOX( injection_method_box ), inject_with_rtl_check_box, 1, 1, 1 );
    gtk_box_pack_start( GTK_BOX( injection_method_box ), inject_with_crt_check_box, 1, 1, 1 );
    gtk_widget_set_sensitive(injection_method_box, FALSE);
    
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(drv_unload_check_button), TRUE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(drv_regent_delete_check_button), TRUE);
    
    gtk_tooltips_set_tip (GTK_TOOLTIPS (button_bar_tips), drv_unload_check_button,
     				 "Unload driver after it has been successfuly loaded.",
     				 NULL);
    gtk_tooltips_set_tip (GTK_TOOLTIPS (button_bar_tips), drv_delete_check_button,
     				 "Delete driver after it has been successfuly loaded / unloaded.",
     				 NULL);
    gtk_tooltips_set_tip (GTK_TOOLTIPS (button_bar_tips), zwset_check_button,
     				 "You cannot unload or delete driver loaded this way.",
     				 NULL);
    gtk_tooltips_set_tip (GTK_TOOLTIPS (button_bar_tips), ntload_check_button,
     				 "The best way to load driver, it can be unloaded and removed.",
     				 NULL);
    gtk_tooltips_set_tip (GTK_TOOLTIPS (button_bar_tips), servmanag_check_button,
     				 "Default way in which driver should be loaded, but not the best.",
     				 NULL);
    gtk_tooltips_set_tip (GTK_TOOLTIPS (button_bar_tips), use_injection_check_button,
     				 "If this is checked, driver loading routine will be injected\n\
into another process. Next on the right you can type process\n\
name, by default our target process is explorer.exe.",
     				 NULL);
     				  
    sep1 = gtk_hseparator_new (); 
    sep2 = gtk_hseparator_new ();
    sep3 = gtk_hseparator_new ();
    sep4 = gtk_hseparator_new ();
//    sep5 = gtk_hseparator_new ();
//    sep6 = gtk_hseparator_new ();
    sep7 = gtk_hseparator_new ();  
    
    load_button = gtk_button_new_from_stock(GTK_STOCK_EXECUTE);
    about_button = gtk_button_new_from_stock(GTK_STOCK_ABOUT);
    quit_button = gtk_button_new_from_stock(GTK_STOCK_QUIT);
    
    driver_label = gtk_label_new(NULL);
    method_label = gtk_label_new(NULL);
    exit_action_label = gtk_label_new(NULL);
    os_version_label = gtk_label_new(NULL);
    os_version_label_ex = gtk_label_new(NULL);
 //   nt_functions_label = gtk_label_new(NULL);
  //  nt_functions_label_ex = gtk_label_new(NULL);
    use_injection_label = gtk_label_new(NULL);
    target_process_label = gtk_label_new(NULL);
    targ_proc_entry = gtk_entry_new();
    
    gtk_label_set_markup(GTK_LABEL(driver_label), "<span size=\"large\"> Select Driver:    </span>");
    gtk_label_set_markup(GTK_LABEL(method_label), "<span size=\"large\"> Select Method: </span>");
    gtk_label_set_markup(GTK_LABEL(exit_action_label), "<span size=\"large\"> Exit Action:       </span>");
//    gtk_label_set_markup(GTK_LABEL(os_version_label), "<span size=\"large\"> OS Version:      </span>");
 //   gtk_label_set_markup(GTK_LABEL(nt_functions_label), "<span size=\"large\"> NT Functions:   </span>");
    gtk_label_set_markup(GTK_LABEL(use_injection_label), "<span size=\"large\"> Use Injection?:  </span>");
    gtk_label_set_markup(GTK_LABEL(target_process_label), "<span size=\"large\"> | Process: </span>");
    gtk_widget_set_sensitive(target_process_label, FALSE);
    gtk_entry_set_text (GTK_ENTRY(targ_proc_entry), "explorer.exe");
    gtk_widget_set_sensitive(targ_proc_entry, FALSE);
    gtk_entry_set_width_chars(GTK_ENTRY(targ_proc_entry), 15);
    gtk_entry_set_has_frame (GTK_ENTRY(targ_proc_entry), FALSE);
    /*
    if(!GetVersionEx(&VersionInfo))
    {
      gtk_label_set_markup(GTK_LABEL(os_version_label_ex), "<span size=\"large\"> Could not get OS Version! </span>");
    } else {
      sprintf(container, "<span size=\"large\"> Windows %d.%d.%d %s </span>", VersionInfo.dwMajorVersion, VersionInfo.dwMinorVersion, VersionInfo.dwBuildNumber, VersionInfo.szCSDVersion);
      gtk_label_set_markup(GTK_LABEL(os_version_label_ex), container);
    }
    */
    /*
    sprintf(nt_functions_container, "<span size=\"small\"> NtLoadDriver: <b>0x%08x</b>, ZwSetSystemInformation: <b>0x%08x</b>, \n\
 RtlInitUnicodeString: <b>0x%08x</b>, RtlAdjustPrivilege: <b>0x%08x</b>, \n\
 NtClose: <b>0x%08x</b>, NtUnloadDriver: <b>0x%08x</b> \n\
 NtCurrentTeb: <b>0x%08x</b>, RtlAllocateHeap: <b>0x%08x</b>, \n\
 NtQuerySystemInformation: <b>0x%08x</b>, RtlFreeHeap: <b>0x%08x</b>, \n\
 NtOpenProcess: <b>0x%08x</b>, NtAllocateVirtualMemory: <b>0x%08x</b>, \n\
 NtWriteVirtualMemory: <b>0x%08x</b>, RtlCreateUserThread: <b>0x%08x</b>. </span>", 
    NtLoadDriver, ZwSetSystemInformation, RtlInitUnicodeString, RtlAdjustPrivilege, NtClose, NtUnloadDriver,
    Nt_CurrentTeb, RtlAllocateHeap, NtQuerySystemInformation, RtlFreeHeap, NtOpenProcess,
    NtAllocateVirtualMemory, NtWriteVirtualMemory, RtlCreateUserThread);
    
    gtk_label_set_markup(GTK_LABEL(nt_functions_label_ex), nt_functions_container);
    */
    picker = gtk_file_chooser_button_new ("Select Driver to load", 
                                          GTK_FILE_CHOOSER_ACTION_OPEN);
                                          
    button_box = gtk_hbox_new(0,0);
    gtk_box_pack_start( GTK_BOX( button_box ), load_button, 1, 1, 1 );
    gtk_box_pack_start( GTK_BOX( button_box ), about_button, 1, 1, 1 );
    gtk_box_pack_start( GTK_BOX( button_box ), quit_button, 1, 1, 1 );
    
    injection_box = gtk_hbox_new(0,0);
    gtk_box_pack_start( GTK_BOX( injection_box ), use_injection_label, 0, 0, 0 );
    gtk_box_pack_start( GTK_BOX( injection_box ), use_injection_check_button, 0, 0, 0 );
    
    gtk_box_pack_start( GTK_BOX( injection_box ), target_process_label, 0, 0, 0 );
    gtk_box_pack_start( GTK_BOX( injection_box ), targ_proc_entry, 0, 0, 0 );
    
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER); // where we want to appear main application when launched
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300); // main app size
    gtk_window_set_decorated(GTK_WINDOW(window), TRUE); // window borders
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE); // we cannot maximize app now, set TRUE if want
    
    g_signal_connect (G_OBJECT (window), "destroy",
		      G_CALLBACK (destroy), NULL); // when X pressed

        description_label = gtk_label_new(NULL);
        gtk_label_set_markup(GTK_LABEL(description_label), "\n<span size=\"large\"><b>DLoad (Driver Loader)</b></span>\n");
        main_box = gtk_vbox_new( 0, 0 );
        load_box = gtk_hbox_new(0,0);
        method_box = gtk_hbox_new(0,0);
        methods_box = gtk_vbox_new( 0, 0 );
        exit_action_box = gtk_hbox_new(0,0);
        exit_actions_box = gtk_vbox_new( 0, 0 );
//        os_version_box = gtk_hbox_new(0,0);
//        nt_functions_box = gtk_hbox_new(0,0);
        
//        targ_proc_entry = gtk_entry_new();
        gtk_box_pack_start( GTK_BOX( HeaderBox ), description_label, 1, 1, 1 );
  //      gtk_box_pack_start( GTK_BOX( HeaderBox ), frame, 0, 0, 0 );
        gtk_box_pack_start( GTK_BOX( methods_box ), zwset_check_button, 0, 0, 0 );
        gtk_box_pack_start( GTK_BOX( methods_box ), ntload_check_button, 0, 0, 0 );
        gtk_box_pack_start( GTK_BOX( methods_box ), servmanag_check_button, 0, 0, 0 );
        
        gtk_box_pack_start( GTK_BOX( load_box ), driver_label, 0, 0, 0 );
        gtk_box_pack_start( GTK_BOX( load_box ), picker, 1, 1, 1 );
        gtk_box_pack_start( GTK_BOX( method_box ), method_label, 0, 0, 0 );
        gtk_box_pack_start( GTK_BOX( method_box ), methods_box, 0, 0, 0 );
        gtk_box_pack_start( GTK_BOX( exit_action_box ), exit_action_label, 0, 0, 0 );
        gtk_box_pack_start( GTK_BOX( exit_actions_box ), drv_unload_check_button, 0, 0, 0 );
        gtk_box_pack_start( GTK_BOX( exit_actions_box ), drv_delete_check_button, 0, 0, 0 );
        gtk_box_pack_start( GTK_BOX( exit_actions_box ), drv_regent_delete_check_button, 0, 0, 0 );
        gtk_box_pack_start( GTK_BOX( exit_action_box ), exit_actions_box, 0, 0, 0 );
//        gtk_box_pack_start( GTK_BOX( os_version_box ), os_version_label, 0, 0, 0 );
//        gtk_box_pack_start( GTK_BOX( os_version_box ), os_version_label_ex, 0, 0, 0 );
//        gtk_box_pack_start( GTK_BOX( nt_functions_box ), nt_functions_label, 0, 0, 0 );
//        gtk_box_pack_start( GTK_BOX( nt_functions_box ), nt_functions_label_ex, 0, 0, 0 );
        
        gtk_container_add( GTK_CONTAINER( window ), main_box );
        gtk_box_pack_start( GTK_BOX( main_box ), HeaderBox, 0, 0, 0 );
        gtk_box_pack_start( GTK_BOX( main_box ), sep1, 0, 0, 0 );
        gtk_box_pack_start( GTK_BOX( main_box ), load_box, 0, 0, 0 );
        gtk_box_pack_start( GTK_BOX( main_box ), sep3, 0, 0, 0 );
        gtk_box_pack_start( GTK_BOX( main_box ), method_box, 0, 0, 0 );
        gtk_box_pack_start( GTK_BOX( main_box ), sep4, 0, 0, 0 );
        gtk_box_pack_start( GTK_BOX( main_box ), exit_action_box, 0, 0, 0 );
        gtk_box_pack_start( GTK_BOX( main_box ), sep2, 0, 0, 0 );
//        gtk_box_pack_start( GTK_BOX( main_box ), os_version_box, 0, 0, 0 );
  //      gtk_box_pack_start( GTK_BOX( main_box ), sep5, 0, 0, 0 );
        gtk_box_pack_start( GTK_BOX( main_box ), injection_box, 0, 0, 0 );
        gtk_box_pack_start( GTK_BOX( main_box ), injection_method_box, 0, 0, 0 );
        gtk_box_pack_start( GTK_BOX( main_box ), sep7, 0, 0, 0 );
//        gtk_box_pack_start( GTK_BOX( main_box ), nt_functions_box, 0, 0, 0 );
//        gtk_box_pack_start( GTK_BOX( main_box ), sep6, 0, 0, 0 );
        gtk_box_pack_end( GTK_BOX( main_box ), button_box, 1, 1, 1 );

//============================== functions
	gtk_signal_connect (GTK_OBJECT (quit_button), "clicked", 
		GTK_SIGNAL_FUNC(destroy), window);
	gtk_signal_connect (GTK_OBJECT (about_button), "clicked", 
		GTK_SIGNAL_FUNC(About_DLoad), window);
	gtk_signal_connect (GTK_OBJECT (load_button), "clicked", 
		GTK_SIGNAL_FUNC(Load_Driver), window);
//***********************************************************
	gtk_signal_connect (GTK_OBJECT (zwset_check_button), "toggled", 
		GTK_SIGNAL_FUNC(SetUpZwOption), window);
	gtk_signal_connect (GTK_OBJECT (servmanag_check_button), "toggled", 
		GTK_SIGNAL_FUNC(SetUpScOption), window);
	gtk_signal_connect (GTK_OBJECT (ntload_check_button), "toggled", 
		GTK_SIGNAL_FUNC(SetUpNtOption), window);
	gtk_signal_connect (GTK_OBJECT (use_injection_check_button), "toggled", 
		GTK_SIGNAL_FUNC(SetUpInjectionOption), window);
//=================================================================
    gtk_widget_show_all  (window);
    gtk_main ();
    return 0;
}

int Load_Driver(){
    char *filename; char *name;
    bool zwset_state, ntload_state, servman_state, unload_state, delete_state, delete_regent_state, use_inj_state;
   	HKEY hk; BOOL en;
   	NTSTATUS Status;
   	char Storage[MAX_PATH];
	DWORD Type = SERVICE_KERNEL_DRIVER;
	char ImagePath[MAX_PATH] = "\\??\\"; 
	char RegPath[MAX_PATH] = "SYSTEM\\CurrentControlSet\\Services\\";
	WCHAR RegUniPath[MAX_PATH] = L"\\Registry\\Machine\\SYSTEM\\CurrentControlSet\\Services\\";
	UNICODE_STRING u_str;
	wchar_t file_name[MAX_PATH];
	wchar_t driver_full_path[MAX_PATH] = L"\\??\\";
	SYSTEM_LOAD_AND_CALL_IMAGE img;
    const	char *target_process;
     
    zwset_state = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(zwset_check_button));
    ntload_state = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(ntload_check_button));
    servman_state = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(servmanag_check_button));
    unload_state = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(drv_unload_check_button));
    delete_state = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(drv_delete_check_button));
    delete_regent_state = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(drv_regent_delete_check_button));
    use_inj_state = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(use_injection_check_button));
    target_process = gtk_entry_get_text(GTK_ENTRY(targ_proc_entry));

    filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (picker));
    name = PathFindFileName(filename);

//===================== using injection =============================//
    if(use_inj_state == TRUE){
//===================== ############### =============================//
//                        MessageBox(0, "using injection into ...(proc name in mb title)", target_process,0);
                          
                        if(zwset_state == TRUE){
                                          
		                LoadDriverWithInjection((char *)target_process, filename, ZWLOADMODE, FALSE, FALSE, FALSE);
                        
                        } else if(ntload_state == TRUE){
                               
                        LoadDriverWithInjection((char *)target_process, filename, NTLOADMODE, unload_state, delete_state, delete_regent_state);       
                                                  
                        } else if(servman_state == TRUE){

                        LoadDriverWithInjection((char *)target_process, filename, SMLOADMODE, unload_state, delete_state, delete_regent_state);             
                        }
                     
    } 
//===================== not using injection =========================//    
    else {
//         MessageBox(0,"not using injection","LOL",0);
  //       return 0;
//===================== ############### =============================//
    if(zwset_state == TRUE){
                   unload_state == FALSE;
                   delete_state == FALSE;
                   char Debug[MAX_PATH];
                   int Size = sizeof(SYSTEM_LOAD_AND_CALL_IMAGE);
                   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(drv_unload_check_button), FALSE);
                   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(drv_delete_check_button), FALSE);
                   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(drv_regent_delete_check_button), FALSE);
                   
                   MultiByteToWideChar(CP_ACP, 0, filename, -1, file_name, sizeof(file_name));
                   wcscat(driver_full_path, file_name);
                   
                   RtlInitUnicodeString(&(img.ModuleName),driver_full_path);
                   RtlAdjustPrivilege(10, TRUE, AdjustCurrentProcess, &en);
                   
                   
                   if(Status = ZwSetSystemInformation(SystemLoadAndCallImage,&img,sizeof(SYSTEM_LOAD_AND_CALL_IMAGE)) != STATUS_SUCCESS){
                   sprintf(Storage, "Could not load driver! STATUS: 0x%08x", Status);
                   MessageBox(0, Storage, "ERROR", MB_ICONERROR);  
                   RtlZeroMemory(Storage, sizeof(Storage)); 
                   return FALSE;                                                                                       
                   }
                   
    } else if (ntload_state == TRUE){
 
           strcat(ImagePath, filename); 
           strcat(RegPath, name);
           MultiByteToWideChar(CP_ACP, 0, name, -1, file_name, sizeof(file_name));
           wcscat(RegUniPath, file_name);
           RtlInitUnicodeString(&u_str, RegUniPath); 
              
           if (RegCreateKey(HKEY_LOCAL_MACHINE, RegPath, &hk) == STATUS_SUCCESS)
           {
         		RegSetValueEx(hk, "ImagePath", 0, REG_SZ, (LPBYTE)ImagePath, strlen(ImagePath)+1); 
		        RegSetValueEx(hk, "Type", 0, REG_DWORD, (LPBYTE)&Type, sizeof(DWORD));  
                RegCloseKey(hk); 
                RtlAdjustPrivilege(10, TRUE, AdjustCurrentProcess, &en);
                		 if(Status = NtLoadDriver(&u_str) != STATUS_SUCCESS){
                         sprintf(Storage, "Could not load driver! STATUS: 0x%08x", Status);
			             MessageBox(0,Storage,"ERROR",MB_ICONERROR);
			             RtlZeroMemory(Storage, sizeof(Storage)); 
			             return FALSE;
                         }      
                                          
           } else {
		     MessageBox(0,"Unable to create registry values","ERROR",0);
		     return FALSE;
           }
           if(unload_state == TRUE){
                           if(NtUnloadDriver(&u_str) != STATUS_SUCCESS)MessageBox(0, "Unable to unload driver!", "ERROR", MB_ICONERROR);
                           }
           if(delete_state == TRUE){
                           DeleteFile(filename);
                           }
           if(delete_regent_state == TRUE){
                           MyDeleteKey(HKEY_LOCAL_MACHINE, RegPath);
                           }
           
    } else if (servman_state == TRUE){
           gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(drv_regent_delete_check_button), FALSE);
           if(!RunDriverWithServiceManager(name, filename)){
           MessageBox(0, "Loading driver error!", "ERROR", MB_ICONERROR);
           return FALSE;
           }
           if(unload_state == TRUE){
                           if(!RemoveDriverWithServiceManager(name, filename)){
                           MessageBox(0, "Unloading driver error!", "ERROR", MB_ICONERROR);
                           return FALSE;
                           }
                           }
           if(delete_state == TRUE){
                           DeleteFile(filename);
                           }
    }
}
    
    return 0;
}


static void destroy( GtkWidget *widget, gpointer   data ){
    gtk_main_quit ();
}

void About_DLoad(){
GtkWidget* dial, *lab, *vbox, *butt;
dial =  gtk_dialog_new();
gtk_window_position (GTK_WINDOW (dial), GTK_WIN_POS_MOUSE);

  const gchar *authors[] = {
    "cross / csrss <cross@x1machine.com>",
    NULL
  };

const gchar *documentors[] = { 
"cross <cross@x1machine.com>\n\n\
[+] Load driver with ZwSetSystemInformation\n\
[+] Load driver with NtLoadDriver\n\
[+] Load driver with Service Control Manager\n\
[+] Unload driver\n\
[+] Delete driver file\n\
[+] Delete driver rigistry entries\n\
[+] Injection of driver loading routine into another process\n\
[+] Injection with CreateRemoteThread\n\
[+] Injection with RtlCreateUserThread",
NULL
};

  const gchar *license = "GNU LESSER GENERAL PUBLIC LICENSE Version 3";
    
      gtk_show_about_dialog (GTK_WINDOW (dial),
			 "program-name", "DLoad",
			 "version", PACKAGE_VERSION,
			 "copyright", "(C) 2008-2009 x1machine project",
			 "license", license,
			 "website", "www.x1machine.com",
			 "comments", "DLoad designed to load newly coded drivers\n\
in a simple way- you can select how do you want your\n\
driver to be loaded:\n\n\
1. via ZwSetSystemInformation\n\
2. via NtLoadDriver\n\
3. via Service Manager\n\n\
After driver is loaded it will be automatically unloaded.\n\
This app designed to quickly check driver functionality\n\
and unload it.\n\
Version 2.0 introduces possibility of injecting\n\
driver loading routing into another process,\n\
it could be user process or system process.\n\
Injection uses same settings so it would load\n\
driver in the same way like without injection, \n\
with usage of the above 3 methods.",
			 "authors", authors,
			 "documenters", documentors,
             "title", "About DLoad",
			 NULL);
 return ;   
}
   
bool NtFunctionsInit(){
     const char NTDLL[] = { 0x6e, 0x74, 0x64, 0x6c, 0x6c, 0x2e, 0x64, 0x6c, 0x6c, 0x00 };
     HMODULE hObsolete                      = GetModuleHandle(NTDLL);
     *(FARPROC *)&RtlInitUnicodeString	    = GetProcAddress(hObsolete, "RtlInitUnicodeString");
     *(FARPROC *)&NtLoadDriver	            = GetProcAddress(hObsolete, "NtLoadDriver");
     *(FARPROC *)&NtUnloadDriver	        = GetProcAddress(hObsolete, "NtUnloadDriver");
     *(FARPROC *)&ZwSetSystemInformation	= GetProcAddress(hObsolete, "ZwSetSystemInformation");
     *(FARPROC *)&NtClose	                = GetProcAddress(hObsolete, "NtClose");
     *(FARPROC *)&RtlAdjustPrivilege	    = GetProcAddress(hObsolete, "RtlAdjustPrivilege");
	 *(FARPROC *)&Nt_CurrentTeb				= GetProcAddress(hObsolete, "NtCurrentTeb");
	 *(FARPROC *)&RtlAllocateHeap			= GetProcAddress(hObsolete, "RtlAllocateHeap");
	 *(FARPROC *)&NtQuerySystemInformation	= GetProcAddress(hObsolete, "NtQuerySystemInformation");
	 *(FARPROC *)&RtlFreeHeap				= GetProcAddress(hObsolete, "RtlFreeHeap");
	 *(FARPROC *)&NtOpenProcess				= GetProcAddress(hObsolete, "NtOpenProcess");
	 *(FARPROC *)&NtAllocateVirtualMemory	= GetProcAddress(hObsolete, "NtAllocateVirtualMemory");
	 *(FARPROC *)&NtWriteVirtualMemory		= GetProcAddress(hObsolete, "NtWriteVirtualMemory");
	 *(FARPROC *)&RtlCreateUserThread		= GetProcAddress(hObsolete, "RtlCreateUserThread");
	 if(RtlInitUnicodeString && NtLoadDriver && NtUnloadDriver &&
		 ZwSetSystemInformation && NtClose && RtlAdjustPrivilege && 
		 Nt_CurrentTeb && RtlAllocateHeap && NtQuerySystemInformation &&
		 RtlFreeHeap && NtOpenProcess && NtAllocateVirtualMemory &&
		 NtWriteVirtualMemory && RtlCreateUserThread){
	 return TRUE;
	 }
return FALSE; 
}

BOOL RunDriverWithServiceManager(char *ServiceName, char *DriverPath){
BOOL Status = FALSE;

	SC_HANDLE ServiceHandle = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
	if (ServiceHandle == NULL) return FALSE;

	SC_HANDLE ServiceHandleEx = CreateService(ServiceHandle, ServiceName, ServiceName,  
		SERVICE_START | DELETE | SERVICE_STOP, SERVICE_KERNEL_DRIVER, 
		SERVICE_DEMAND_START, SERVICE_ERROR_IGNORE, DriverPath, NULL, 
		NULL, NULL, NULL, NULL);
		
	if(ServiceHandleEx == NULL){		
		ServiceHandleEx = OpenService(ServiceHandle, ServiceName, SERVICE_START | DELETE | SERVICE_STOP);
		if(ServiceHandleEx == NULL)	goto end;
	}

	if (!StartService(ServiceHandleEx, 0, NULL)) goto end;

	Status = TRUE;

end:
	CloseServiceHandle(ServiceHandleEx);
	CloseServiceHandle(ServiceHandle);
	
	return Status;
}

BOOL RemoveDriverWithServiceManager(char *ServiceName, char *DriverPath){
	SC_HANDLE ServiceHandle = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
	if (ServiceHandle == NULL) return FALSE;

	SC_HANDLE ServiceHandleEx = OpenService(ServiceHandle, ServiceName, SERVICE_START | DELETE | SERVICE_STOP);
	if(ServiceHandleEx == NULL)	return FALSE;
	
	SERVICE_STATUS status;
	ControlService(ServiceHandleEx, SERVICE_CONTROL_STOP, &status);

    DeleteService(ServiceHandleEx);
    CloseServiceHandle(ServiceHandleEx);
	CloseServiceHandle(ServiceHandle);

	return TRUE;     
     
}

// copyright by microsoft, following code has been stolen
// from MS website by me xD
BOOL RegDelnodeRecurse (HKEY hKeyRoot, LPTSTR lpSubKey)
{
    LPTSTR lpEnd;
    LONG lResult;
    DWORD dwSize;
    TCHAR szName[MAX_PATH];
    HKEY hKey;
    FILETIME ftWrite;

    // First, see if we can delete the key without having
    // to recurse.

    lResult = RegDeleteKey(hKeyRoot, lpSubKey);
    if (lResult == ERROR_SUCCESS) return TRUE;
    lResult = RegOpenKeyEx (hKeyRoot, lpSubKey, 0, KEY_READ, &hKey);

    if (lResult != ERROR_SUCCESS){
        if (lResult == ERROR_FILE_NOT_FOUND) {
            MessageBox(0, "Key not found!", "ERROR", MB_ICONERROR);
            return TRUE;
        } else {
            MessageBox(0, "Error opening key!", "ERROR", MB_ICONERROR);
            return FALSE;
        }
    }

    // Check for an ending slash and add one if it is missing.

    lpEnd = lpSubKey + lstrlen(lpSubKey);

    if (*(lpEnd - 1) != TEXT('\\')){
        *lpEnd =  TEXT('\\');
        lpEnd++;
        *lpEnd =  TEXT('\0');
    }

    // Enumerate the keys

    dwSize = MAX_PATH;
    lResult = RegEnumKeyEx(hKey, 0, szName, &dwSize, NULL, NULL, NULL, &ftWrite);

    if (lResult == ERROR_SUCCESS){
        do {
 
            strcpy (lpEnd, szName);
            if (!RegDelnodeRecurse(hKeyRoot, lpSubKey)) {break;}

            dwSize = MAX_PATH;
            lResult = RegEnumKeyEx(hKey, 0, szName, &dwSize, NULL, NULL, NULL, &ftWrite);

        } while (lResult == ERROR_SUCCESS);
    }
     
    lpEnd--;
    *lpEnd = TEXT('\0');
    RegCloseKey (hKey);

    // Try again to delete the key.

    lResult = RegDeleteKey(hKeyRoot, lpSubKey);
    if (lResult == ERROR_SUCCESS) return TRUE;
    return FALSE;
}
// coz i wanted to find implementation of SHDeleteKey
// and found this

BOOL MyDeleteKey (HKEY hKeyRoot, LPTSTR lpSubKey)
{
    TCHAR szDelKey[MAX_PATH*2];
    strcpy (szDelKey, lpSubKey);
    return RegDelnodeRecurse(hKeyRoot, szDelKey);

}
