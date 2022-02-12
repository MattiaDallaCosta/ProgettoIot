#!/usr/bin/env python3
from datetime import datetime
from flask import Flask, render_template
from flask_restful import Resource, Api, reqparse
from flask_sqlalchemy import SQLAlchemy

# Configs
app = Flask(__name__)
api = Api(app)
db = SQLAlchemy(app)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///./progettoiot.db'

# DB config blueprints
class IOTDB(db.Model):
    __tablename__ = 'progettoiot'

    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String)
    score = db.Column(db.Integer)
    date = db.Column(db.DateTime)

    # to return JSON object wher requested
    def to_json(self):
        date_time = self.date.strftime("%m/%d/%Y, %H:%M:%S")
        return {
            'id'       : self.id,
            'username' : self.username,
            'score'    : self.score,
            'date'     : date_time
        }

    def __repr__(self):
        return f"<IOTDB(id={self.id}, username={self.username}, score={self.score}, date={self.date})>"

# Api endpoint
# Api req. parser
parser = reqparse.RequestParser()
parser.add_argument('username')
parser.add_argument('score')
class iotData(Resource):
    # API /upload - GET
    def get(self):
        query = db.session.query(IOTDB).all()
        res = [i.to_json() for i in query]
        return res, 200

    # API /upload - POST
    def post(self):
        arg = parser.parse_args()
        user = arg["username"]
        score = arg["score"]
        db.session.add(IOTDB(username=user, score=score, date=datetime.now()))
        db.session.commit()

        return {"message" : "success"}, 200

api.add_resource(iotData, '/upload')

# FRONT-END ROUTE
@app.route("/")
def index():
    return render_template("index.html"), 200