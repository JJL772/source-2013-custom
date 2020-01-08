#
#
# Project script for Tier1
#
#
project(vgui_controls C CXX)

# Platform specific sources 
set(WINDOWS_SRCS	)
set(POSIX_SRCS	)

# We need to append damn lzma shit
set(SRCS
		"AnalogBar.cpp"
		"AnimatingImagePanel.cpp"
		"AnimationController.cpp"
		"BitmapImagePanel.cpp"
		"BuildFactoryHelper.cpp"
		"BuildGroup.cpp"
		"BuildModeDialog.cpp"
		"Button.cpp"
		"CheckButton.cpp"
		"CheckButtonList.cpp"
		"CircularProgressBar.cpp"
		"ComboBox.cpp"
		"consoledialog.cpp"
		"ControllerMap.cpp"
		"controls.cpp"
		"cvartogglecheckbutton.cpp"
		"DirectorySelectDialog.cpp"
		"Divider.cpp"
		"EditablePanel.cpp"
		"ExpandButton.cpp"
		"FileOpenDialog.cpp"
		"FileOpenStateMachine.cpp"
		"${ROOT}/public/filesystem_helpers.cpp"
		"FocusNavGroup.cpp"
		"Frame.cpp"
		"GraphPanel.cpp"
		"HTML.cpp"
		"Image.cpp"
		"ImageList.cpp"
		"ImagePanel.cpp"
		"InputDialog.cpp"
		"KeyBindingHelpDialog.cpp"
		"KeyBoardEditorDialog.cpp"
		"KeyRepeat.cpp"
		"Label.cpp"
		"ListPanel.cpp"
		"ListViewPanel.cpp"
		"Menu.cpp"
		"MenuBar.cpp"
		"MenuButton.cpp"
		"MenuItem.cpp"
		"MessageBox.cpp"
		"MessageDialog.cpp"
		"Panel.cpp"
		"PanelListPanel.cpp"
		"PerforceFileExplorer.cpp"
		"PerforceFileList.cpp"
		"perforcefilelistframe.cpp"
		"ProgressBar.cpp"
		"ProgressBox.cpp"
		"PropertyDialog.cpp"
		"PropertyPage.cpp"
		"PropertySheet.cpp"
		"QueryBox.cpp"
		"RadioButton.cpp"
		"RichText.cpp"
		"RotatingProgressBar.cpp"
		"savedocumentquery.cpp"
		"ScalableImagePanel.cpp"
		"ScrollableEditablePanel.cpp"
		"ScrollBar.cpp"
		"ScrollBarSlider.cpp"
		"SectionedListPanel.cpp"
		"Slider.cpp"
		"Splitter.cpp"
		"subrectimage.cpp"
		"TextEntry.cpp"
		"TextImage.cpp"
		"ToggleButton.cpp"
		"Tooltip.cpp"
		"ToolWindow.cpp"
		"TreeView.cpp"
		"TreeViewListControl.cpp"
		"URLLabel.cpp"
		"WizardPanel.cpp"
		"WizardSubPanel.cpp"
		"${ROOT}/vgui2/src/vgui_key_translation.cpp"
)

# Preprocessor defs
set(DEFINES )

# Platform-specific preprocessor defines
set(WIN32_DEFINES	)	
set(POSIX32_DEFINES	)
set(WIN64_DEFINES	)
set(POSIX64_DEFINES	)
set(WINDOWS_DEFINES	)
set(POSIX_DEFINES	)

set(PLATFORM_64BIT_DEFINES	)
set(PLATFORM_32BIT_DEFINES 	)

# Links dirs to search for link libs in
set(LINK_DIRS	)
set(WINDOWS_LINK_DIRS	)
set(POSIX_LINK_DIRS		)
set(WIN32_LINK_DIRS		)
set(WIN64_LINK_DIRS		)
set(POSIX32_LINK_DIRS	)
set(POSIX64_LINK_DIRS	)

# Generic libs to link against
set(LINK_LIBS	)

# Platform specific link libs
set(WIN32_LINK_LIBS		)
set(WIN64_LINK_LIBS		)
set(POSIX32_LINK_LIBS	)
set(POSIX64_LINK_LIBS	)

# Generic include dirs
set(INCLUDE_DIRS		${PUBLIC_INCLUDE}/tier1 ${PUBLIC_INCLUDE}/tier0
${ROOT}/thirdparty ${ROOT}/thirdparty/cef generated_proto)

# Platform specific includes
set(WIN32_INCLUDE_DIRS	)
set(WIN64_INCLUDE_DIRS	)
set(POSIX32_INCLUDE_DIRS	)
set(POSIX64_INCLUDE_DIRS	)

# Set the variable of target for stuff
set(TARGET vgui_controls)

# Set the output file name
set(OUTPUT_FILE_NAME vgui_controls)

# If this is a shared lib
set(SHARED_LIB 0)

# If this is a static lib
set(STATIC_LIB 1)

# Include this to handle all the defines
include(${CMAKESCRIPTS_DIR}/library-base.cmake)

