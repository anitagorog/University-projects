module com.example.a7_map {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires com.dlsc.formsfx;

    opens main.a7_map to javafx.fxml;
    exports main.a7_map;
    exports main;
    opens main to javafx.fxml;
}