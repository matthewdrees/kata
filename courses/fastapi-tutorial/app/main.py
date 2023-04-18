from enum import Enum
from fastapi import FastAPI
from pydantic import BaseModel
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

class Item(BaseModel):
    name: str
    description: Union[str, None] = None
    price: float
    tax: Union[float, None] = None

l = []

@app.post("/items/")
async def create_item(item: Item):
    item_dict = item.dict()
    if item.tax:
        price_with_tax = item.price + item.tax
        item_dict.update({"price_with_tax": price_with_tax})
    l.append(item_dict)
    return item

@app.get("/all_items/")
async def get_all_items():
    return {"all_items":l}
