package com.example.miniproject
import android.os.Bundle
import android.view.View
import android.widget.CompoundButton
import android.widget.TextView
import android.widget.ToggleButton
import androidx.appcompat.app.AppCompatActivity
import com.google.firebase.database.*


class MainActivity : AppCompatActivity() {
    var switch: ToggleButton? = null
    var Suhu: TextView? = null
    var Humidity: TextView? = null
    var Servo: TextView? = null
    var valueSuhu: String? = null
    var valueHumi: String? = null
    var valueServo: String? = null
    var switchValue: String? = null
    var dref: DatabaseReference? = null
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        switch = findViewById<View>(R.id.toggleButton_switch) as ToggleButton

        Suhu = findViewById<View>(R.id.txtView_valueSuhu) as TextView
        Humidity = findViewById<View>(R.id.txtView_valueHumi) as TextView
        Servo = findViewById<View>(R.id.txtView_valueServo) as TextView
        dref = FirebaseDatabase.getInstance().getReference()
        dref!!.addValueEventListener(object : ValueEventListener {
            override fun onDataChange(dataSnapshot: DataSnapshot) {
                switchValue = dataSnapshot.child("data/switch").getValue().toString()
                if (switchValue == "1") {
                    valueSuhu = dataSnapshot.child("data/temperature").getValue().toString()
                    Suhu!!.text = valueSuhu
                    valueHumi = dataSnapshot.child("data/humidity").getValue().toString()
                    Humidity!!.text = valueHumi
                    valueServo = dataSnapshot.child("data/Servo").getValue().toString()
                    Servo!!.text = valueServo
                }else{
                    valueSuhu="0"
                    valueServo="0"
                    valueHumi= "0"
                }
            }

            override fun onCancelled(databaseError: DatabaseError) {}
        })
        switch!!.setOnCheckedChangeListener(CompoundButton.OnCheckedChangeListener { buttonView, isChecked ->
            if (isChecked) {
                val on_Off = FirebaseDatabase.getInstance().getReference("data/switch")
                on_Off.setValue(1)
            } else {
                val on_Off = FirebaseDatabase.getInstance().getReference("data/switch")
                on_Off.setValue(0)
            }
        })
    }
}