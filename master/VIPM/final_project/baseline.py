# Disable CPU optimization warnings (we run on GPU)
import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

import keras
import keras.layers as layers
import tensorflow as tf
import matplotlib.pyplot as plt

size2D = (224, 224)
size3D = (224, 224, 3)


batch_size = 64
train_ds = keras.utils.image_dataset_from_directory('data/train', labels='inferred', label_mode='int', image_size=size2D, batch_size=batch_size)
valid_ds = keras.utils.image_dataset_from_directory('data/valid', labels='inferred', label_mode='int', image_size=size2D, batch_size=batch_size)
test_ds = keras.utils.image_dataset_from_directory('data/test', labels='inferred', label_mode='int', image_size=size2D, batch_size=batch_size)

class_names = train_ds.class_names

plt.figure(figsize=(10, 10))
for images, labels in train_ds.take(1):
  for i in range(9):
    ax = plt.subplot(3, 3, i + 1)
    plt.imshow(images[i].numpy().astype("uint8"))
    plt.title(class_names[labels[i]])
    plt.axis("off")
    


# Prepare for performance
AUTOTUNE = tf.data.AUTOTUNE
train_ds = train_ds.cache().shuffle(1000).prefetch(buffer_size=AUTOTUNE)
valid_ds = valid_ds.cache().prefetch(buffer_size=AUTOTUNE)


baseline = keras.models.Sequential()
baseline.add(keras.Input(shape=size3D))

baseline.add(layers.Rescaling(1./255))

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
epochs = 10

baseline.compile(loss='sparse_categorical_crossentropy', optimizer='adam', metrics=['accuracy'])
history = baseline.fit(train_ds, epochs=epochs, validation_data=valid_ds)

def plot_performance(history):
	acc = history.history['accuracy']
	val_acc = history.history['val_accuracy']

	loss = history.history['loss']
	val_loss = history.history['val_loss']

	epochs_range = range(epochs)

	plt.figure(figsize=(8, 8))
	plt.subplot(1, 2, 1)
	plt.plot(epochs_range, acc, label='Training Accuracy')
	plt.plot(epochs_range, val_acc, label='Validation Accuracy')
	plt.legend(loc='lower right')
	plt.title('Training and Validation Accuracy')

	plt.subplot(1, 2, 2)
	plt.plot(epochs_range, loss, label='Training Loss')
	plt.plot(epochs_range, val_loss, label='Validation Loss')
	plt.legend(loc='upper right')
	plt.title('Training and Validation Loss')
	plt.show()

plot_performance(history)

score = baseline.evaluate(test_ds, verbose=0)
print("test loss: ", score[0])
print("test accuracy: ", score[1])