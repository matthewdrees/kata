# Convert ~70 videos in my mac photos library that wouldn't sync to my iphone
# from *.avi to *.mp4.
#
# When syncing it would pop up several "can't copy this video because it won't
# display on your device" messages. Highly irritating.
#
# Note Handbrake won't preserve the original EXIF date created timestamp. Used ffmpeg on command line.
#
# Cobbled my solution below from these two posts:
# https://superuser.com/questions/523286/how-to-make-handbrake-preserve-capture-time-creation-time
# https://stackoverflow.com/questions/52396602/conversion-from-mjpeg-to-mp4-libx264-with-ffmpeg
#
# Instructions:
#  1. $ brew install ffmpeg
#  2. Search for *.avi in mac Photos app. Select all and export as originals to "movies" folder.
#  3. Run this script to create *.mp4 in "newmovies" folder.
#  4. Verify new mp4 movies work.
#  5. ffmprobe a movie to verify timestamp information was preserved. Photos app doesn't care about filesystem timestamp.
#  6. In Photos app import the new videos and delete the old ones.
import os
import subprocess

for dirpath, dirnames, filenames in os.walk('movies'):
    print(dirpath)
    for filename in filenames:
        infile = os.path.join(dirpath, filename)
        outfile = os.path.join('newmovies', os.path.splitext(filename)[0] + '.mp4')
        cmd = ["ffmpeg", "-i", infile, "-pix_fmt", "yuv420p", "-c:v", "libx264", "-map_metadata", "0", outfile]
        print(" ".join(cmd))
        subprocess.run(cmd)

