import requests
import json

url = "https://whoomp.cs.uwaterloo.ca/458a3/api/plain/send"
payload = {
  "api_token": "18b02d363e372bd22c9c8e8dfe823bf6323c656eb5ca74dc406d1a221256d726",
  "to": "nessie",
  "message": "SGVsbG8sIHdvcmxkIQ=="
}
headers = {
  "content-type": "application/json",
  "accept": "application/json"
}
response = requests.post(url, data=json.dumps(payload), headers=headers)

print(response.text, response.status_code)

url = "https://whoomp.cs.uwaterloo.ca/458a3/api/plain/inbox"
payload = {
  "api_token": "18b02d363e372bd22c9c8e8dfe823bf6323c656eb5ca74dc406d1a221256d726",
}
response = requests.post(url, data=json.dumps(payload), headers=headers)

print(response.text, response.status_code)

