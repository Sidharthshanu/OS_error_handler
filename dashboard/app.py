# File: dashboard/app.py
from flask import Flask, render_template
import collections
import os

app = Flask(__name__)

LOG_FILE = os.path.join(os.path.dirname(os.path.abspath(__file__)), '../logs/error_log.log')

def read_logs():
    try:
        with open(LOG_FILE, 'r') as file:
            return file.readlines()
    except FileNotFoundError:
        return []

@app.route('/')
def index():
    logs = read_logs()[-100:]  # Display the last 100 log entries
    return render_template('index.html', logs=logs)

@app.route('/stats')
def stats():
    stats_counter = collections.Counter()
    logs = read_logs()
    for line in logs:
        if "MEMORY_ERROR" in line:
            stats_counter['MEMORY_ERROR'] += 1
        elif "FILE_ACCESS_ERROR" in line:
            stats_counter['FILE_ACCESS_ERROR'] += 1
        elif "DEVICE_ERROR" in line:
            stats_counter['DEVICE_ERROR'] += 1
        elif "NULL_ERROR" in line:
            stats_counter['NULL_ERROR'] += 1
        else:
            stats_counter['UNKNOWN_ERROR'] += 1
    return render_template('stats.html', stats=stats_counter)

if __name__ == '__main__':
    app.run(debug=True)