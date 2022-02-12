#!/usr/bin/env python3
# init script for server and api

from server import app
import sys, getopt

def main(argv):
   try:
      opts, args = getopt.getopt(argv,"hdp",["dev=","prod=", "help="])
   except getopt.GetoptError:
      print("""Usage: init.py -opt 
         \n \t- '-d' or '--dev' to run dev server 
         \n \t- '-p' or '--prod' to run prod server 
         \n \t- '-h' or '--help' to help.
         """)
      sys.exit(2)
   for opt, arg in opts:
      if opt in ("-h", "-help"):
         print("""Usage: init.py -opt 
         \n \t- '-d' or '--dev' to run dev server 
         \n \t- '-p' or '--prod' to run prod server 
         \n \t- '-h' or '--help' to help.
         """)
         sys.exit()
      elif opt in ("-p", "--prod"):
         app.run()
      elif opt in ("-d", "--dev"):
         app.run(debug=True)

if __name__ == "__main__":
   main(sys.argv[1:])
