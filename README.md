# Lap Counter

Lap Counter is an application to track the laps completed by multiple participants. You can customize the appearance and behavior of the application by editing the `config.json` file.


## Screenshots and Explanations

In this section, we provide screenshots and explanations for both the list and grid display types to help you better understand the Lap-Counter application.

### List Display

The list display shows a simple list of participants with their total laps, last lap, and best lap information. Each participant is displayed on a separate line.

![List Display Screenshot](./screenshots/list-display.png)

In the example above, you can see the names of the participants along with their total laps, last lap, and best lap. The list display is sorted according to the `sortType` configuration option.

### Grid Display

The grid display shows a table with columns for the name, total laps, last lap, and best lap. Each participant is displayed in a separate row.

![Grid Display Screenshot](./screenshots/grid-display.png)

In the example above, you can see the grid displaying the same information as the list display but in a more organized tabular format. The grid display is also sorted according to the `sortType` configuration option.


### Data Analyser Program

This is an external software that can read data from the output files of the Lap-Counter program. There will be more documentation in the future

![Data Analyser Screenshot](./screenshots/data-analyser.png)


## Configuration

To configure the application, update the `config.json` file with the desired settings. Here's an example configuration:
To access the `config.json` you need to right click on the Lap-Counter.exe, choose: open file location and go to the config folder.

```json
{
  "windowTitle": "Lap-Counter",
  "comPort": "COM3",
  "outputDir": "C:/Users/username/Documents/",
  "main": {
    "lapLength": 200,
    "displayType": "grid",
    "sortType": "bestLap"
  },
  "titleRow": {
    "displayed": true,
    "default": "Lap Counter"
  },
  "totalRow": {
    "displayed": true,
    "default": "Total Laps: 0 <br> Estimated Distance: 0m",
    "format": "Total Laps: ${total} <br> Estimated Distance: ${distance}m"
  },
  "list": {
    "format": "${person}: ${totalLaps} laps (Last Lap: ${lastLap}, Best: ${bestLap})"
  },
  "grid": {
    "name": "Name",
    "totalLaps": "Total",
    "lastLap": "Last Lap",
    "bestLap": "Best Lap"
  },
  "names": {
    "default": "P",
    "persons": {
      "1": "",
      "2": "",
      "3": "",
      "4": "",
      "5": "",
      "6": "",
      "7": "",
      "8": "",
      "9": "",
      "10": "",
      "11": "",
      "12": "",
      "13": "",
      "14": "",
      "15": "",
      "16": "",
      "17": "",
      "18": "",
      "19": "",
      "20": ""
    }
  }
}
```

### Configuration options

- `windowTitle` (string): The title of the application window.
  - Example: `"Lap-Counter"`

- `comPort` (string): The COM port used for communication (e.g., "COM3").
  - Example: `"COM3"`
- `outputDir` (string): The directory where the application output files will be saved. 
  - Example `"C:/Users/username/Documents/"`
- `main` (object): Main configuration options.
  - `lapLength` (number): The length of a lap in meters.
    - Example: `200`
  - `displayType` (string): The display type for the application ("list" or "grid").
    - Example: `"grid"`
  - `sortType` (string): The sorting method used for displaying data ("totalLaps" or "bestLap").
    - Example: `"bestLap"`

- `titleRow` (object): Configuration options for the title row.
  - `displayed` (boolean): Whether the title row should be displayed (true or false).
    - Example: `true`
  - `default` (string): The default title for the application.
    - Example: `"Compteur de tours"`

- `totalRow` (object): Configuration options for the total row.
  - `displayed` (boolean): Whether the total row should be displayed (true or false).
    - Example: `true`
  - `default` (string): The default text for the total row.
    - Example: `"Total des tours : 0 <br> Distance estimée : 0m,"`
  - `format` (string): The format string for the total row, using placeholders for dynamic values.
    - Example: `"Total des tours : ${total} <br> Distance estimée : ${distance}m"`

- `list` (object): Configuration options for the list display type.
  - `format` (string): The format string for the list display, using placeholders for dynamic values.
    - Example: `"${person}: ${totalLaps} tours (Dernier tour: ${lastLap}, meilleur: ${bestLap})"`

- `grid` (object): Configuration options for the grid display type.
  - `name` (string): The column title for the name field.
    - Example: `"Nom"`
  - `totalLaps` (string): The column title for the total laps field.
    - Example: `"Total"`
  - `lastLap` (string): The column title for the last lap field.
    - Example: `"Dernier tour"`
  - `bestLap` (string): The column title for the best lap field.
    - Example: `"Meilleur tour"`

- `names` (object): Configuration options for participant names.
  - `default` (string): The default prefix for unnamed participants.
    - Example: `"P"`
  - `persons` (object): An object mapping participant numbers to their names.
    - Example:
      ```
      {
        "1": "John",
        "2": "Ben",
        ...
      }
      ```

### Support and Contact

If you need support or have any questions about the Lap-Counter application, feel free to reach out to us via the [issue tracker on GitHub](https://github.com/guillaumevd/lap-counter/issues). We will be happy to help you with any issues or questions you might have.
