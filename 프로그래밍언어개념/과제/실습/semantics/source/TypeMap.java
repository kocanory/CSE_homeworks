import java.util.*;

public class TypeMap extends HashMap<Variable, Type> { 

    void display() {
        System.out.print("{ ");

        Iterator<Variable> iterator = this.keySet().iterator();
	    while (iterator.hasNext()) {
	    	Variable key = (Variable) iterator.next();
	        System.out.print("<" + key + ", " + this.get(key) + ">");
	        if(iterator.hasNext())
	        	System.out.print(", ");
	    }
	    System.out.println(" }\n");
   	}

}
