# Disable CPU optimization warnings (we run on GPU)
import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

import keras
import keras.layers as layers
import matplotlib.pyplot as plt

size2D = (224, 224)
size3D = (224, 224, 3)

(train_x, train_y) = keras.utils.image_dataset_from_directory('data/train', labels='inferred', label_mode='int', image_size=size2D)
valid = keras.utils.image_dataset_from_directory('data/valid', labels='inferred', label_mode='int', image_size=size2D)
(test_x, test_y) = keras.utils.image_dataset_from_directory('data/test', labels='inferred', label_mode='int', image_size=size2D)


baseline = keras.models.Sequential()
baseline.add(keras.Input(shape=size3D))

baseline.add(layers.Conv2D(64, kernel_size=3, activation='relu'))
baseline.add(layers.MaxPool2D(pool_size=2))

baseline.add(layers.Conv2D(128, kernel_size=3, activation='relu')),
baseline.add(layers.MaxPool2D(pool_size=4))

baseline.add(layers.Conv2D(256, kernel_size=3, activation='relu'),)
baseline.add(layers.MaxPool2D(pool_size=4),)

baseline.add(layers.Flatten(),)
baseline.add(layers.Dropout(0.3),)

baseline.add(layers.Dense(100, activation='softmax'))

baseline.summary()



# Training

batch_size = 64
epochs = 10

baseline.compile(loss='sparse_categorical_crossentropy', optimizer='adam', metrics=['accuracy'])

history = baseline.fit(train_x, train_y, batch_size=batch_size, epochs=epochs, validation_data=valid)

def plot_performance(history):
  fig, ax = plt.subplots(1, 2)
  fig.tight_layout()
  train_acc = history.history['accuracy']
  valid_acc = history.history['val_accuracy']
  train_loss = history.history['loss']
  valid_loss = history.history['val_loss']
  ax[0].set_xlabel('Epoch')
  ax[0].set_ylabel('Loss')
  ax[0].set_title('Loss')
  ax[0].plot(train_loss)
  ax[0].plot(valid_loss)
  ax[1].set_title('Accuracy')
  ax[1].set_xlabel('Epoch')
  ax[1].set_ylabel('Accuracy')
  ax[1].plot(train_acc)
  ax[1].plot(valid_acc)
  plt.show()

plot_performance(history)

score = baseline.evaluate(test_x, test_y, verbose=0)
print("test loss: ", score[0])
print("test accuracy: ", score[1])