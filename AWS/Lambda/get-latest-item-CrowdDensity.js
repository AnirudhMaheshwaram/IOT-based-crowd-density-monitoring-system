const AWS = require('aws-sdk')
const docClient = new AWS.DynamoDB.DocumentClient()

// async function abstraction
async function getItem(id)
{
  var params = 
      {
    TableName : 'crowd_density_frequent',                        // dynamodb table name
    Key: { date_string: '99999999999999' }                       // key itemusing which we will access
  }
  try 
  {
    const data = await docClient.get(params).promise()           // getting data
    return data                                                  // returns data
    
  } 
  catch (err) 
  {
    return err                                                  // returns error
  }
}

// usage
exports.handler = async (event, context) => {
  try 
  {
    const data = await getItem()                                // waiting for item to get
    const response = 
          {
        statusCode: 200,
        headers: 
            {
          "Access-Control-Allow-Origin": "*",
          "Access-Control-Allow-Headers": "*",
          "Access-Control-Allow-Methods": "*"
        },
        body: JSON.stringify(data),                             // converts java script value to json format
    };
    context.succeed(response);                                  
  } 
  catch (err) 
  {
    return { error: err }
  }
}
