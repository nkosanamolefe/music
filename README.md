## Qt Music CD Manager

This document describes a Qt application for storing and displaying music CD information. 

### Model

The application utilizes the Qt `QStandardItemModel` to manage the CD data. The model stores the following information for each CD:

* Composer (string)
* Album Name (string)
* Replacement Value (double)
* Rating (integer, out of 100)

### View

The data is displayed in a table format. Here are the key functionalities of the view:

* **Header Row:** The table includes a header row displaying labels for each data field (Composer, Album Name, Replacement Value, Rating).
* **Adding Rows:** Users can add new rows to the model to enter information for additional CDs.
* **Replacement Value Formatting:** The replacement value is always displayed in cents format, even if the value is zero (e.g., "R10.00").
* **Rating Bar Delegate:** A custom delegate is used to display the rating as a horizontal bar that fills the remaining space in the rating column.
* **Sorting:** Users can click on the column headers to sort the data by the corresponding field (composer, album name, replacement value, or rating).
* **Conditional Row Coloring:** Rows with a replacement value of R200 or more are displayed in a different color. This color updates dynamically when the user edits the replacement value (changes back to normal if the value falls below R200).
* **Deleting Rows:** Users can delete unwanted rows of data from the table.

###  Example Interface

An image showcasing the expected user interface should be included here (not possible to generate in text format). The image should depict the table with header row, data entries, and visual representations of the functionalities mentioned above (rating bar, conditional row coloring).

### Dependencies

This application relies on the Qt framework, specifically the `Qt Model/View` classes.
