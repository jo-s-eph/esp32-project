import requests
import base64
import urllib

# Spotify credentials
CLIENT_ID = "CLIENT_ID"
CLIENT_SECRET = "CLIENT_SECRET"
REDIRECT_URI = "http://localhost:8080"
SCOPE = "user-read-currently-playing user-library-modify"

# Step 1: Generate the authorization URL
auth_url = (
    f"https://accounts.spotify.com/authorize?"
    f"client_id={CLIENT_ID}&response_type=code&redirect_uri={REDIRECT_URI}&scope={urllib.parse.quote(SCOPE)}"
)
print("Visit this URL to authorize the app:", auth_url)

# Step 2: After user authorizes, they will be redirected to your REDIRECT_URI with a "code" parameter.
# Copy that code and paste it below.
auth_code = input("Enter the authorization code: ")

# Step 3: Exchange authorization code for access token
token_url = "https://accounts.spotify.com/api/token"
auth_header = base64.b64encode(f"{CLIENT_ID}:{CLIENT_SECRET}".encode()).decode()
headers = {"Authorization": f"Basic {auth_header}"}
data = {
    "grant_type": "authorization_code",
    "code": auth_code,
    "redirect_uri": REDIRECT_URI,
}

response = requests.post(token_url, headers=headers, data=data)
response_json = response.json()
access_token = response_json["access_token"]
refresh_token = response_json["refresh_token"]

print("Access Token:", access_token)
print("Refresh Token:", refresh_token)