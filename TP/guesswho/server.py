import http.server
import json
import os
import urllib
import urllib.parse
import random

from apiclient.discovery import build
from http.server import BaseHTTPRequestHandler, HTTPServer
from urllib.request import urlretrieve

# global variables
names = './names.json';
credits = './credits.txt';

creds = ();
service = None;
people_list = [];

# Global State
current_person_idx = 0;
user_level = 10;
user_score = 0;

# Requests. 
def build_service(key):
    return build("customsearch", "v1", developerKey=key);

def execute_request(service, cx_id, request,):
    return service.cse().list(
        q=request,
        cx=cx_id,
        searchType='image',
        num=1,
        imgType='clipart',
        fileType='png',
        safe= 'off'
    ).execute();

def get_image(service, cx_id, objs, idx):
    query = objs[idx]['name'] + ' ' + objs[idx]['description'] + ' photo';
    print('Query: ', query);
    res = execute_request(service, cx_id, query);
    assert 'items' in res;
    print('Res: ', res['items'][0]['link']);
    return res['items'][0]['link'];

# Credits. 
def get_credits(filename):
    with open(filename) as cfile:
        credits = cfile.read().replace('\n', '').split(' ');
    return (credits[0], credits[1]);

# Read names list. 
def get_object(filename):
    with open(filename) as jfile:
        json_string = jfile.read();
    return json.loads(json_string);

# User's guess.
def get_submit_data(text):
    name = people_list[current_person_idx]['name'];
    answ = text[0];
    print("Text: ", text, " Name: ", name);
    global user_score;
    if answ.lower() == name.lower():
        user_score += 1;
    return str(user_score);

# Load new image.
def get_image_data():

    global current_person_idx;
    global people_list;

    print("Load new image");
    print("User level: ", user_level);

    new_idx = int(random.randrange(0, user_level));
    print("New idx:", new_idx);

    if 'path' in people_list[new_idx]:
        print('Use buffered result.');
        image_path = people_list[new_idx]['path'];
    else:
        print('Search image.');
        #print('Download image.');
        image_path = get_image(service, creds[1], people_list, new_idx);
        people_list[new_idx]['path'] = image_path;
        print('Update people_list: ', people_list[new_idx]);
    current_person_idx = new_idx;
    return image_path;

# Server side shit

def send_data(self, data, memtype):
    self.send_response(200)
    self.send_header('Content-type', memtype)
    self.end_headers()
    self.wfile.write(data)
    return

def load_file(path):
    data = "";
    with open(path, "rb") as ffile:
        data = ffile.read();
    return data;

class testHTTPServer_RequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        global user_score;
        qs = urllib.parse.urlparse(self.path);
        qc = urllib.parse.parse_qs(qs.query);

        print("QC: ", qc);
        print("PATH: ", self.path);

        data = "";
        memtype = "text/html";

        if "/image" == self.path: # Load new image
            data = bytes(get_image_data(), "utf-8");
            memtype = 'text/plain'
        elif "submit" in qc: # User's guess.
            data = bytes(get_submit_data(qc["submit"]), "utf-8")
            memtype = 'text/plain'
        elif "level" in qc: # Set level and reture game page
            global user_level
            user_level = int(qc["level"][0]);
            data = load_file('game.html');
            user_score = 0;
        else:
            data = load_file('index.html');
            user_score = 0;

        send_data(self, data , memtype);
        return
 
def run():
  server_address = ('0.0.0.0', 8080)
  httpd = HTTPServer(server_address, testHTTPServer_RequestHandler)
  httpd.serve_forever()

def main():
    global people_list;
    global creds;
    global service;
    global current_person_idx;

    create_dir(path_db);
    creds       = get_credits(credits);
    service     = build_service(creds[0]);
    people_list = get_object(names);
    current_person_idx = 0;
    run();

main()
