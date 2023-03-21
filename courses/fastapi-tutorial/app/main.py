from enum import Enum
from fastapi import FastAPI
from typing import Union
import time

app = FastAPI()


@app.get("/")
def hello_world():
    return {"message": "take 1"}

@app.get("/items/{item_id}")
def hello_world(item_id:str, q: Union[str, None] = None, short: bool = False):
    item = {"item_id": item_id}
    if q:
        item.update({"q": q})
    if short:
        item.update({"description": "This is a description"})
    return item


class AnimalName(str, Enum):
    pig = "pig"
    cow = "cow"

@app.get("/animals/{animal_name}")
def get_animal(animal_name:AnimalName):
    if animal_name is AnimalName.pig:
        message = "oink"
    if animal_name is AnimalName.cow:
        message = "moo"
    return {"animal_name": animal_name, "message" : message}


@app.get("/skipandlimit/")
async def read_skipandlimit(skip: int = 0, limit: int = 10):
    time.sleep(1.0)
    return {"skip": skip, "limit": limit}

