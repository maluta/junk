# -*- coding: utf-8 -*-

# Convert CDROM content to WAV

import subprocess
import CDDB, DiscID

cdrom = DiscID.open()
disc_id = DiscID.disc_id(cdrom)

(query_status, query_info) = CDDB.query(disc_id)
(read_status, read_info) = CDDB.read(query_info['category'], query_info['disc_id'])

for i in range(disc_id[1]):
	name = "%s.wav" % (read_info['TTITLE' + `i`])
        name = name.replace("\xba",".")
	name = name.replace("\"","'")
	name = name.replace(",","")
	if i<9:
		mplayer_cmd="mplayer cdda://%d -ao pcm:file=\"0%d - %s\" " % (i+1,i+1,name)
	else:
		mplayer_cmd="mplayer cdda://%d -ao pcm:file=\"%d - %s\" " % (i+1,i+1,name)

#	print mplayer_cmd
	subprocess.call(mplayer_cmd,shell=True)

