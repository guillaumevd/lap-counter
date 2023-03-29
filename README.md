# Lap Counter

Lap Counter is an application to track the laps completed by multiple participants. You can customize the appearance and behavior of the application by editing the `config.json` file.

## Configuration

To configure the application, update the `config.json` file with the desired settings. Here's an example configuration:

```json
{
  "windowTitle": "Lap-Counter",
  "comPort": "COM3",
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


### Configuration options

- `windowTitle`: The title of the application window.
- `comPort`: The COM port used for communication (e.g., "COM3").
- `main`: Main configuration options.
  - `lapLength`: The length of a lap in meters.
  - `displayType`: The display type for the application ("list" or "grid").
  - `sortType`: The sorting method used for displaying data ("totalLaps" or "bestLap").
- `titleRow`: Configuration options for the title row.
  - `displayed`: Whether the title row should be displayed (true or false).
  - `default`: The default title for the application.
- `totalRow`: Configuration options for the total row.
  - `displayed`: Whether the total row should be displayed (true or false).
  - `default`: The default text for the total row.
  - `format`: The format string for the total row, using placeholders for dynamic values.
- `list`: Configuration options for the list display type.
  - `format`: The format string for the list display, using placeholders for dynamic values.
- `grid`: Configuration options for the grid display type.
  - `name`: The column title for the name field.
  - `totalLaps`: The column title for the total laps field.
  - `lastLap`: The column title for the last lap field.
  - `bestLap`: The column title for the best lap field.
- `names`: Configuration options for participant names.
  - `default`: The default prefix for unnamed participants.
  - `persons`: An object mapping participant numbers to their names.
