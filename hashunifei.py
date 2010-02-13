# -*- coding: utf-8 -*-
# Tiago Maluta <maluta@unifei.edu.br> 

import simplejson, urllib
import twitter 

list_id = []

#
api = twitter.Api(username='USERNAME', password='PASSWORD')

SEARCH_BASE = 'http://search.twitter.com/'
url = SEARCH_BASE + "search.json?q=UNIFEI+OR+efei"

def publish(user,text):
	twitt = "@"+user+" "+text

	if len(twitt) > 140:
		twitt = twitt[:140]

	api.PostUpdates(twitt)


result = simplejson.load(urllib.urlopen(url))['results']

with open(".hashunifei","r+") as f:
    data = f.read()
    list_id = data.split(",") 

f = open(".hashunifei","a")
for twitt in result:

	text = twitt['text']
	user = twitt['from_user']
	
	if user != "hashunifei":
		id = str(twitt['id'])
		if id not in list_id:	
			list_id.append(id)
			f.write(id+',')
			publish(user,text)
f.close() 
