#!/user/bin/env python3
#initialize database

from server import db, IOTDB
from datetime import datetime

def createDB():
    print("Creating DB")
    db.create_all()

def insertData():
    db.session.add(IOTDB(username='Giovanni', score=12, date=datetime.now()))
    db.session.commit()

if __name__ == '__main__':
    createDB()
    # insertData()
    