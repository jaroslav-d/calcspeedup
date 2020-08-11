package com.example.matrixmultiply;

import android.os.Build;
import android.support.annotation.RequiresApi;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;


public class MainActivity extends AppCompatActivity {

    TextView tv;

    EditText etOne;
    EditText etTwo;
    EditText etThree;
    EditText etFour;
    EditText etFive;
    EditText etSix;

    Button button;

    SWIGTYPE_p_p_int resultC;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        button = findViewById(R.id.button);
        button.setOnClickListener(new View.OnClickListener() {
            @RequiresApi(api = Build.VERSION_CODES.N)
            @Override
            public void onClick(View v) {
                etOne = findViewById(R.id.num_a);
                etTwo = findViewById(R.id.num_b);
                etThree = findViewById(R.id.num_c);
                etFour = findViewById(R.id.num_threads);
                etFive = findViewById(R.id.type_schedule);
                etSix = findViewById(R.id.chunk_size);
                int a = Integer.parseInt(etOne.getText().toString());
                int b = Integer.parseInt(etTwo.getText().toString());
                int c = Integer.parseInt(etThree.getText().toString());
                int numThreads = Integer.parseInt(etFour.getText().toString());
                int typeSchedule = Integer.parseInt(etFive.getText().toString());
                int chunkSize = Integer.parseInt(etSix.getText().toString());
                int[][] result;
                int[][] matrixA;
                int[][] matrixB;

                // call C/C++ methods from Java and calc lead time
                resultC = example.initMatrix(a,b,b,c);
                result = getJavaMatrixFromResultC(resultC);
                long start = System.currentTimeMillis();
                example.parallelMatrixMultiply(resultC, numThreads, typeSchedule, chunkSize);
                long stop = System.currentTimeMillis();
                long timeCalc = stop - start;

                // data processing for see
                result = getJavaMatrixFromResultC(resultC);
                String stringTextView;
//                stringTextView = resultToString(result);
                stringTextView = "A time parallel calc: " + timeCalc + "\n";
                // Example of a call to a native method
                tv = findViewById(R.id.sample_text);
                tv.setText(stringTextView);
            }
        });
    }

    private String resultToString(int[][] result) {
        String s = "";
        for (int[] row : result) {
            for (int element : row) {
                s = s.concat(element + "\t");
            }
            s = s.concat("\n");
        }
        return s;
    }

    /** method for get Java integer type array from C/C++ integer array*/
    private int[][] getJavaMatrixFromResultC(SWIGTYPE_p_p_int resultC){
        int[][] result = new int[example.getRa()][example.getCb()];
        for (int row = 0; row < example.getRa(); row++) {
            for (int column = 0; column < example.getCb(); column++) {
                result[row][column] = example.getItemFromMatrix(resultC,row,column);
            }
        }
        return result;
    }

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("example");
    }
}
