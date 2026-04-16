from flask import Flask, request, redirect, url_for, render_template, flash
from werkzeug.utils import secure_filename
import os
from datetime import datetime

app = Flask(__name__)


UPLOAD_FOLDER = 'static/captured_images/'
ALLOWED_EXTENSIONS = {'jpg', 'jpeg', 'png', 'gif'}
MAX_CONTENT_LENGTH = 0.5 * 1024 * 1024  # 500KB

app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER
app.config['MAX_CONTENT_LENGTH'] = MAX_CONTENT_LENGTH
app.secret_key = 'NguyenHau'


def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

# Route để hiển thị form upload
@app.route('/')
def index():
    return render_template('index.html')

# Route để upload file
@app.route('/uploads', methods=['POST'])
def upload_file():
    if 'imageFile' not in request.files:
        flash('No file part')
        return redirect(request.url)

    file = request.files['imageFile']

    if file.filename == '':
        flash('No selected file')
        return redirect(request.url)

    if file and allowed_file(file.filename):
        filename = secure_filename(file.filename)
        date_string = datetime.now().strftime('%Y-%m-%d_%H%M%S_')
        target_file = os.path.join(app.config['UPLOAD_FOLDER'], date_string + filename)

        if os.path.exists(target_file):
            flash("Sorry, file already exists.")
            return redirect(url_for('index'))

        try:
            file.save(target_file)
            flash('Photo uploaded successfully.')
            return redirect(url_for('view_images'))
        except Exception as e:
            flash(f"Sorry, there was an error: {str(e)}")
            return redirect(url_for('index'))

    flash('Invalid file format. Only JPG, JPEG, PNG & GIF are allowed.')
    return redirect(url_for('index'))

# Route để hiển thị tất cả các ảnh đã upload
@app.route('/view')
def view_images():
    images = os.listdir(app.config['UPLOAD_FOLDER'])
    return render_template('view.html', images=images)

# Khởi chạy ứng dụng Flask
if __name__ == "__main__":
    if not os.path.exists(UPLOAD_FOLDER):
        os.makedirs(UPLOAD_FOLDER)
    app.run(host='0.0.0.0', port=5000, debug=True)
