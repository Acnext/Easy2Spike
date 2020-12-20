from keras.preprocessing.image import ImageDataGenerator
from keras.models import Sequential, load_model
from keras.layers import Activation, Dropout, Flatten, Reshape, Dense, Concatenate, GlobalMaxPooling2D
from keras.layers import BatchNormalization, Input, Conv2D, Lambda, Average
from keras.applications.inception_v3 import InceptionV3
from keras.callbacks import ModelCheckpoint
from keras import metrics
from keras.optimizers import Adam
from keras import backend as K
import keras
from keras.models import Model
model = Sequential()
model.add(Dense(units=64, activation='relu', input_dim=100))
model.add(Dense(units=10, activation='softmax'))
#model.layers[-2].trainable = False
for x in model.trainable_weights:
    print(x.name)
print('\n')