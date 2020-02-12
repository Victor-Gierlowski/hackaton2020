import React from 'react';
import { StyleSheet, Text, View, Button, TouchableWithoutFeedback, TouchableOpacity,} from 'react-native';




export default function App() {

  return (
    <View style={{ flex:1, backgroundColor: 'yellow' }}>
      <View style={{ flex:1, alignItems: 'center', justifyContent: 'center',  height: 335, backgroundColor: 'white' }}>
      <TouchableOpacity style={styles.customBtnBG} onPress={() => {}}>
<Text style={styles.customBtnText}>Pour moi</Text>
</TouchableOpacity>
</View>
      <View style={{ flex:1, alignItems: 'center', justifyContent: 'center',  height: 335, backgroundColor: 'black' }}><TouchableOpacity style={styles.customBtnBG2} onPress={() => {}}>
<Text style={styles.customBtnText2}>Pour autrui</Text>
</TouchableOpacity></View>
    </View>
  )
}
const styles = StyleSheet.create({
/* Here style the text of your button */
customBtnText: {
fontSize: 80,
fontWeight: "bold",
color: "orange",
},

/* Here style the background of your button */
customBtnBG: {
backgroundColor: "black",
paddingHorizontal: 40,
paddingVertical: 5,
borderRadius: 35
},
/* Here style the text of your button */
customBtnText2: {
fontSize: 69,
fontWeight: "bold",
color: "black",
},

/* Here style the background of your button */
customBtnBG2: {
backgroundColor: "orange",
paddingHorizontal: 30,
paddingVertical: 5,
borderRadius: 35
}
});
