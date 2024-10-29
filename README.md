# Order Management System

## Description
- My Solution Involves using two Classes : API_CLIENT & ORDER_MANAGER
- The segregation was done to make the components modular and independent 
- The API_CLIENT handles the logic for authentication and also handles all the logic for making requests to the DERIBIT API
- The Order_Manager implements the funtions that are exposed to the user to acheive the various functionality mentioned in the task

## Table of Contents
- [Dependencies](#dependencies)
- [Usage](#usage)

## Dependencies

Apart from iostream I have used two external libraries to implement the functionality
- CURL :- This was used to make the API REQUESTS 
- [nlohmann/json](#https://github.com/nlohmann/json) :- This was used to handle the json data t=received as response from the api calls, It provided clean methods to process the json data obtained as response

## Usage

Firstly the documentation could be generated form Doxyfile by running the following command
```
$  doxygen Doxyfile
```
and the html or latex can then be accesed from docs/html && docs/latex respectively
then do the following to generate the executable

```
    // Note the commands have to be performed from the root of the project
   $ mkdir build  && cd build
   $ make
```
Before Running the executable set the required environment variables
```
    $ export DERIBIT_CLIENT_ID="your-client-id-here"
    $ export DERIBIT_CLIENT_SECRET="your-client-secret-here"
```
and then run the executable from the build directory using the command 
```
    $ ./OrderExecutionSystem
```
## Examples

    ```md
    ![alt text](assets/images/screenshot.png)
    ```

## Features

Features That could be implemented
- A CLI App using qt or other frameworks to make the experience more hands on for the user 
- Implement functionality for making asynchronous requests