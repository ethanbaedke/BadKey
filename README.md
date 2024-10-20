# Imagelyn

# Build Instructions
1) Clone the repository on to your Windows(x64) machine
2) Run the GenerateProject.bat file
3) Open the Imagelyn.sln file it generates

# Game Customization Instructions
1) Open the data folder, all changes will be made in this folder. Do not modify any files outside of this folder.
2) Modify the PreferenceInit and NameInit text files for your game. These are both abosultely necessary for the game to run and should not be deleted. Documentation for these files is shown below.

PreferenceInit.txt  
    add_preference "insert-name"  
        - Adds a preference that clients can have  

NameInit.txt  
    name "insert-name"  
        - Adds a name that clients can have  

3) The PreferenceInit file must contain at least three preferences for the game to run. The NameInit file must contain at least three names for the game to run.
4) Add as many text files as you choose to define locations for your game. Use the example location files for reference. Documentation for location files is shown below.

MyLocation.txt  
    location "insert-name"  
        - Defines a location. Only one location can be defined per file.  
    activity "insert-name"  
        - Defines an activity. This must be defined after a location. You can define as many activities for a location as you want.  
    preference+ "insert-name"  
        - Adds a positive preference to the most recently defined activity. You can add as many positive preferences to an activity as you want.  
    preference- "insert-name"  
        - Adds a negative preference to the most recently defined activity. You can add as many negative preferences to an activity as you want.  

5) Once you have made your own location file, you can delete the example location files.
6) Below is an example of all the previously described files. Continue making and testing your game. Thank you for building a world with Imagelyn!

PreferenceInit.txt  
    add_preference "ExamplePreference1"  
    add_preference "ExamplePreference2"  
    add_preference "ExamplePreference3"  

NameInit.txt  
    name "ClientName1"  
    name "ClientName2"  
    name "ClientName3"  

MyLocation.txt  
    location "MyLocation"  
        activity "ExampleActivity1"  
            preference+ "ExamplePreference1"  
            preference- "ExamplePreference2"  
            preference+ "ExamplePreference3"  
        activity "ExampleActivity2"  
            preference- "ExamplePreference1"  
            preference+ "ExamplePreference2"  
            preference- "ExamplePreference3"  
        activity "ExampleActivity2"  
            preference+ "ExamplePreference1"  
            preference+ "ExamplePreference2"  
            preference+ "ExamplePreference3"  
