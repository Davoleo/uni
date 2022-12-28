from flask import Flask, render_template
import random

app = Flask(__name__)

# Image List
images = [
	"https://www.animatedimages.org/data/media/209/animated-cat-image-0072.gif",
	"https://www.animatedimages.org/data/media/209/animated-cat-image-0056.gif",
	"https://www.animatedimages.org/data/media/209/animated-cat-image-0394.gif",
	"https://www.animatedimages.org/data/media/209/animated-cat-image-0338.gif",
	"https://www.animatedimages.org/data/media/209/animated-cat-image-0058.gif",
	"https://www.animatedimages.org/data/media/209/animated-cat-image-0184.gif",
	"https://www.animatedimages.org/data/media/209/animated-cat-image-0459.gif"
]

@app.route('/')
def index():
	url = random.choice(images)
	return render_template('index.html', url=url)

if __name__ == "__main__":
	app.run(host="0.0.0.0")