
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.stage.Stage;


import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class SimplePlot extends Application {

    
    double[] readCSV(String filename) {
        try {
            BufferedReader br = new BufferedReader(new FileReader(filename));
            String line = br.readLine();  // read first line
            String[] tokens = line.split(","); // split by comma
            double[] data = new double[tokens.length];
            for (int i = 0; i < tokens.length; i++) {
                data[i] = Double.parseDouble(tokens[i]);  // convert to double
            }
            br.close();
            return data;
        } catch (IOException e) {
            System.out.println("Error reading file: " + filename);
            return null;
        }
    }

    @Override
    public void start(Stage stage) {
        stage.setTitle("CN vs FTCS Graph");

        
        double[] cn = readCSV("cn_solution.csv");
        double[] ftcs = readCSV("ftcs_solution.csv");
        double[] error = readCSV("error.csv");

        
        NumberAxis xAxis = new NumberAxis();
        NumberAxis yAxis = new NumberAxis();
        xAxis.setLabel("Rod points (x)");
        yAxis.setLabel("Temperature / Error");

        
        LineChart<Number, Number> lineChart = new LineChart<>(xAxis, yAxis);

        
        XYChart.Series seriesCN = new XYChart.Series();
        seriesCN.setName("CN");

        XYChart.Series seriesFTCS = new XYChart.Series();
        seriesFTCS.setName("FTCS");

        XYChart.Series seriesError = new XYChart.Series();
        seriesError.setName("Error");

        
        for (int i = 0; i < cn.length; i++) {
            seriesCN.getData().add(new XYChart.Data(i, cn[i]));
            seriesFTCS.getData().add(new XYChart.Data(i, ftcs[i]));
            seriesError.getData().add(new XYChart.Data(i, error[i]));
        }

        
        lineChart.getData().addAll(seriesCN, seriesFTCS, seriesError);

        
        Scene scene = new Scene(lineChart, 800, 600);
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch(args); // launch JavaFX application
    }
}
