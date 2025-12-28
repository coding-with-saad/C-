import React, { useState } from 'react';
import { LineChart, Line, XAxis, YAxis, CartesianGrid, Tooltip, Legend, ScatterChart, Scatter } from 'recharts';
import { Play, RefreshCw, Info } from 'lucide-react';

const LinearRegressionDemo = () => {
  const [learningRate, setLearningRate] = useState(0.01);
  const [iterations, setIterations] = useState(100);
  const [isTraining, setIsTraining] = useState(false);
  const [results, setResults] = useState(null);
  const [showCode, setShowCode] = useState(false);

  // Sample dataset: Study Hours vs Exam Score
  const dataset = [
    { hours: 1, score: 55 },
    { hours: 2, score: 60 },
    { hours: 3, score: 65 },
    { hours: 4, score: 70 },
    { hours: 5, score: 75 },
    { hours: 6, score: 82 },
    { hours: 7, score: 88 },
    { hours: 8, score: 92 },
    { hours: 9, score: 95 },
    { hours: 10, score: 98 }
  ];

  // Linear Regression Implementation from Scratch
  const trainLinearRegression = () => {
    setIsTraining(true);
    
    // Extract X (features) and y (target)
    const X = dataset.map(d => d.hours);
    const y = dataset.map(d => d.score);
    const n = X.length;

    // Initialize parameters
    let m = 0; // slope
    let b = 0; // intercept
    const costHistory = [];

    // Gradient Descent
    for (let iter = 0; iter < iterations; iter++) {
      let predictions = X.map(x => m * x + b);
      
      // Calculate error
      let errors = predictions.map((pred, i) => pred - y[i]);
      
      // Calculate cost (MSE)
      let cost = errors.reduce((sum, err) => sum + err * err, 0) / (2 * n);
      costHistory.push({ iteration: iter + 1, cost: cost.toFixed(2) });
      
      // Calculate gradients
      let dm = errors.reduce((sum, err, i) => sum + err * X[i], 0) / n;
      let db = errors.reduce((sum, err) => sum + err, 0) / n;
      
      // Update parameters
      m = m - learningRate * dm;
      b = b - learningRate * db;
    }

    // Generate prediction line
    const predictionLine = dataset.map(d => ({
      hours: d.hours,
      predicted: m * d.hours + b,
      actual: d.score
    }));

    // Calculate R² score
    const yMean = y.reduce((sum, val) => sum + val, 0) / n;
    const ssTot = y.reduce((sum, val) => sum + Math.pow(val - yMean, 2), 0);
    const ssRes = y.reduce((sum, val, i) => sum + Math.pow(val - (m * X[i] + b), 2), 0);
    const r2Score = 1 - (ssRes / ssTot);

    setResults({
      slope: m.toFixed(4),
      intercept: b.toFixed(4),
      r2Score: r2Score.toFixed(4),
      costHistory: costHistory.slice(-20), // Last 20 iterations
      predictionLine,
      finalCost: costHistory[costHistory.length - 1].cost
    });

    setIsTraining(false);
  };

  const resetModel = () => {
    setResults(null);
    setLearningRate(0.01);
    setIterations(100);
  };

  const pythonCode = `# Linear Regression Implementation from Scratch
import numpy as np
import matplotlib.pyplot as plt

class LinearRegression:
    def __init__(self, learning_rate=0.01, iterations=1000):
        self.learning_rate = learning_rate
        self.iterations = iterations
        self.slope = 0
        self.intercept = 0
        self.cost_history = []
    
    def fit(self, X, y):
        """Train the model using Gradient Descent"""
        n = len(X)
        
        for i in range(self.iterations):
            # Make predictions
            y_pred = self.slope * X + self.intercept
            
            # Calculate error
            error = y_pred - y
            
            # Calculate cost (MSE)
            cost = np.sum(error ** 2) / (2 * n)
            self.cost_history.append(cost)
            
            # Calculate gradients
            d_slope = np.sum(error * X) / n
            d_intercept = np.sum(error) / n
            
            # Update parameters
            self.slope -= self.learning_rate * d_slope
            self.intercept -= self.learning_rate * d_intercept
        
        return self
    
    def predict(self, X):
        """Make predictions"""
        return self.slope * X + self.intercept
    
    def score(self, X, y):
        """Calculate R² score"""
        y_pred = self.predict(X)
        ss_tot = np.sum((y - np.mean(y)) ** 2)
        ss_res = np.sum((y - y_pred) ** 2)
        return 1 - (ss_res / ss_tot)

# Example Usage
# Dataset: Study Hours vs Exam Score
X = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9, 10])
y = np.array([55, 60, 65, 70, 75, 82, 88, 92, 95, 98])

# Create and train model
model = LinearRegression(learning_rate=0.01, iterations=1000)
model.fit(X, y)

# Make predictions
predictions = model.predict(X)

# Evaluate model
r2 = model.score(X, y)
print(f"Slope: {model.slope:.4f}")
print(f"Intercept: {model.intercept:.4f}")
print(f"R² Score: {r2:.4f}")

# Predict for new data
new_hours = 7.5
predicted_score = model.predict(new_hours)
print(f"Predicted score for {new_hours} hours: {predicted_score:.2f}")

# Plot results
plt.figure(figsize=(12, 5))

# Plot 1: Data and Regression Line
plt.subplot(1, 2, 1)
plt.scatter(X, y, color='blue', label='Actual Data')
plt.plot(X, predictions, color='red', linewidth=2, label='Regression Line')
plt.xlabel('Study Hours')
plt.ylabel('Exam Score')
plt.title('Linear Regression: Study Hours vs Exam Score')
plt.legend()
plt.grid(True, alpha=0.3)

# Plot 2: Cost Function over Iterations
plt.subplot(1, 2, 2)
plt.plot(model.cost_history, color='green', linewidth=2)
plt.xlabel('Iterations')
plt.ylabel('Cost (MSE)')
plt.title('Cost Function Convergence')
plt.grid(True, alpha=0.3)

plt.tight_layout()
plt.show()

# Using Scikit-learn (Industry Standard)
from sklearn.linear_model import LinearRegression as SklearnLR
from sklearn.metrics import r2_score, mean_squared_error

# Reshape data for sklearn
X_sklearn = X.reshape(-1, 1)

# Create and train model
sklearn_model = SklearnLR()
sklearn_model.fit(X_sklearn, y)

# Make predictions
sklearn_predictions = sklearn_model.predict(X_sklearn)

# Evaluate
print("\\n--- Using Scikit-learn ---")
print(f"Slope: {sklearn_model.coef_[0]:.4f}")
print(f"Intercept: {sklearn_model.intercept_:.4f}")
print(f"R² Score: {r2_score(y, sklearn_predictions):.4f}")
print(f"MSE: {mean_squared_error(y, sklearn_predictions):.4f}")`;

  return (
    <div className="w-full max-w-6xl mx-auto p-6 bg-gradient-to-br from-blue-50 to-indigo-50 rounded-lg shadow-lg">
      <div className="bg-white rounded-lg p-6 mb-6 shadow">
        <h1 className="text-3xl font-bold text-indigo-900 mb-2">Linear Regression Implementation</h1>
        <p className="text-gray-600">Interactive demonstration of Linear Regression using Gradient Descent</p>
      </div>

      {/* Dataset Display */}
      <div className="bg-white rounded-lg p-6 mb-6 shadow">
        <h2 className="text-xl font-semibold text-gray-800 mb-3 flex items-center gap-2">
          <Info className="w-5 h-5 text-blue-600" />
          Dataset: Study Hours vs Exam Score
        </h2>
        <div className="grid grid-cols-5 gap-4 text-sm">
          {dataset.map((d, i) => (
            <div key={i} className="bg-blue-50 p-3 rounded border border-blue-200">
              <div className="font-semibold text-blue-900">{d.hours} hrs</div>
              <div className="text-gray-600">{d.score} score</div>
            </div>
          ))}
        </div>
      </div>

      {/* Controls */}
      <div className="bg-white rounded-lg p-6 mb-6 shadow">
        <h2 className="text-xl font-semibold text-gray-800 mb-4">Training Parameters</h2>
        <div className="grid grid-cols-1 md:grid-cols-2 gap-6 mb-4">
          <div>
            <label className="block text-sm font-medium text-gray-700 mb-2">
              Learning Rate: {learningRate}
            </label>
            <input
              type="range"
              min="0.001"
              max="0.1"
              step="0.001"
              value={learningRate}
              onChange={(e) => setLearningRate(parseFloat(e.target.value))}
              className="w-full"
            />
            <p className="text-xs text-gray-500 mt-1">Controls step size in gradient descent</p>
          </div>
          <div>
            <label className="block text-sm font-medium text-gray-700 mb-2">
              Iterations: {iterations}
            </label>
            <input
              type="range"
              min="10"
              max="1000"
              step="10"
              value={iterations}
              onChange={(e) => setIterations(parseInt(e.target.value))}
              className="w-full"
            />
            <p className="text-xs text-gray-500 mt-1">Number of training iterations</p>
          </div>
        </div>

        <div className="flex gap-4">
          <button
            onClick={trainLinearRegression}
            disabled={isTraining}
            className="flex items-center gap-2 bg-indigo-600 text-white px-6 py-3 rounded-lg hover:bg-indigo-700 disabled:bg-gray-400 transition"
          >
            <Play className="w-5 h-5" />
            {isTraining ? 'Training...' : 'Train Model'}
          </button>
          <button
            onClick={resetModel}
            className="flex items-center gap-2 bg-gray-600 text-white px-6 py-3 rounded-lg hover:bg-gray-700 transition"
          >
            <RefreshCw className="w-5 h-5" />
            Reset
          </button>
        </div>
      </div>

      {/* Results */}
      {results && (
        <>
          <div className="bg-white rounded-lg p-6 mb-6 shadow">
            <h2 className="text-xl font-semibold text-gray-800 mb-4">Model Results</h2>
            <div className="grid grid-cols-2 md:grid-cols-4 gap-4">
              <div className="bg-green-50 p-4 rounded-lg border border-green-200">
                <div className="text-sm text-gray-600">Slope (m)</div>
                <div className="text-2xl font-bold text-green-700">{results.slope}</div>
              </div>
              <div className="bg-blue-50 p-4 rounded-lg border border-blue-200">
                <div className="text-sm text-gray-600">Intercept (b)</div>
                <div className="text-2xl font-bold text-blue-700">{results.intercept}</div>
              </div>
              <div className="bg-purple-50 p-4 rounded-lg border border-purple-200">
                <div className="text-sm text-gray-600">R² Score</div>
                <div className="text-2xl font-bold text-purple-700">{results.r2Score}</div>
              </div>
              <div className="bg-orange-50 p-4 rounded-lg border border-orange-200">
                <div className="text-sm text-gray-600">Final Cost</div>
                <div className="text-2xl font-bold text-orange-700">{results.finalCost}</div>
              </div>
            </div>
            <div className="mt-4 p-4 bg-gray-50 rounded-lg border border-gray-200">
              <p className="text-sm text-gray-700">
                <strong>Equation:</strong> Score = {results.slope} × Hours + {results.intercept}
              </p>
              <p className="text-sm text-gray-600 mt-1">
                This means for every additional study hour, the exam score increases by approximately {results.slope} points.
              </p>
            </div>
          </div>

          {/* Visualizations */}
          <div className="grid grid-cols-1 lg:grid-cols-2 gap-6 mb-6">
            <div className="bg-white rounded-lg p-6 shadow">
              <h3 className="text-lg font-semibold text-gray-800 mb-4">Regression Line</h3>
              <ScatterChart width={400} height={300}>
                <CartesianGrid strokeDasharray="3 3" />
                <XAxis dataKey="hours" label={{ value: 'Study Hours', position: 'insideBottom', offset: -5 }} />
                <YAxis label={{ value: 'Exam Score', angle: -90, position: 'insideLeft' }} />
                <Tooltip />
                <Legend />
                <Scatter name="Actual Data" data={results.predictionLine} fill="#3b82f6" />
                <Line 
                  name="Predicted Line" 
                  data={results.predictionLine} 
                  dataKey="predicted" 
                  stroke="#ef4444" 
                  strokeWidth={2}
                  dot={false}
                />
              </ScatterChart>
            </div>

            <div className="bg-white rounded-lg p-6 shadow">
              <h3 className="text-lg font-semibold text-gray-800 mb-4">Cost Function Convergence</h3>
              <LineChart width={400} height={300} data={results.costHistory}>
                <CartesianGrid strokeDasharray="3 3" />
                <XAxis dataKey="iteration" label={{ value: 'Iteration', position: 'insideBottom', offset: -5 }} />
                <YAxis label={{ value: 'Cost (MSE)', angle: -90, position: 'insideLeft' }} />
                <Tooltip />
                <Legend />
                <Line type="monotone" dataKey="cost" stroke="#10b981" strokeWidth={2} />
              </LineChart>
            </div>
          </div>
        </>
      )}

      {/* Python Code */}
      <div className="bg-white rounded-lg p-6 shadow">
        <button
          onClick={() => setShowCode(!showCode)}
          className="text-lg font-semibold text-gray-800 mb-4 flex items-center gap-2 hover:text-indigo-600 transition"
        >
          {showCode ? '▼' : '▶'} Python Implementation Code
        </button>
        {showCode && (
          <pre className="bg-gray-900 text-gray-100 p-4 rounded-lg overflow-x-auto text-sm">
            <code>{pythonCode}</code>
          </pre>
        )}
      </div>

      {/* Instructions */}
      <div className="bg-indigo-50 border border-indigo-200 rounded-lg p-6 mt-6">
        <h3 className="text-lg font-semibold text-indigo-900 mb-2">How to Use:</h3>
        <ol className="list-decimal list-inside space-y-2 text-gray-700">
          <li>Adjust the Learning Rate and Iterations using the sliders</li>
          <li>Click "Train Model" to run the gradient descent algorithm</li>
          <li>Observe how the model learns the relationship between study hours and exam scores</li>
          <li>Check the R² score (closer to 1 means better fit)</li>
          <li>View the cost function convergence to see how the error decreases</li>
          <li>Click "Python Implementation Code" to see the complete code</li>
        </ol>
      </div>
    </div>
  );
};

export default LinearRegressionDemo;