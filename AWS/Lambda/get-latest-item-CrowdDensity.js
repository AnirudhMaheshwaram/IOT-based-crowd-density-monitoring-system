const AWS = require('aws-sdk')
const docClient = new AWS.DynamoDB.DocumentClient()

// async function abstraction
async function getItem(id){
  var params = {
    TableName : 'crowd_density_frequent',
    Key: { date_string: '99999999999999' }
  }
  try {
    const data = await docClient.get(params).promise()
    return data
    
  } catch (err) {
    return err
  }
}

// usage
exports.handler = async (event, context) => {
  try {
    const data = await getItem()
    const response = {
        statusCode: 200,
        headers: {
          "Access-Control-Allow-Origin": "*",
          "Access-Control-Allow-Headers": "*",
          "Access-Control-Allow-Methods": "*"
        },
        body: JSON.stringify(data),
    };
    context.succeed(response);
  } catch (err) {
    return { error: err }
  }
}