
#! /usr/bin/python3
import sys                                                  # Provides access to the variables maintained by interpreter
import boto3                                                # An AWS SDK that is used for dealing with cloud related services
from datetime import datetime                               # Importing date and time values
now = datetime.now()                                        # Assigning current date and time to a variable
date_time_string = now.strftime("%Y%m%d%H%M%S")
date_time_int = int(date_time_string)             # Converting date and time to string format
in_no = int(sys.argv[1])                                    # system argument number 1 is assigned to in count
out_no = int(sys.argv[2])                                   # system argument number 2 is assigned to out count
current_no = int(sys.argv[3])                               # system argument number 3 is assigned to current count
current_date_string = '99999999999999'
# Dynammodb on the left side in next line is variable

dynamodb = boto3.resource('dynamodb')                       # Telling boto3 that we are using the AWS service dynamodb
table = dynamodb.Table("crowd_density_frequent")                      # Selecting the table

# Putting data can be done manually from AWS console or from the code

table.put_item(                                             # Command that puts the data on dynamo
Item = {                                                    # Assigning list of items
'date_string' : date_time_string,                             # Date and time value
'date_time' : date_time_int,                             # Date and time value
'In' : in_no,                                               # An item under the table that describes number of people those who are in
'Out' : out_no,                                             # An item under the table that describes number of people those who went out
'Current' : current_no,                                     # An item under the table that describes number of people those who are currently inside
}
)

table.put_item(                                             # Command that puts the data on dynamo
Item = {                                                    # Assigning list of items
'date_string' : current_date_string,                             # Date and time value
'date_time' : date_time_int,                             # Date and time value
'In' : in_no,                                               # An item under the table that describes number of people those who are in
'Out' : out_no,                                             # An item under the table that describes number of people those who went out
'Current' : current_no,                                     # An item under the table that describes number of people those who are currently inside
}
)
