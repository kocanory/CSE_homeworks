import java.util.*;

public class TypeMap extends HashMap<Variable, Type> {

    public void display() {
        Iterator<Entry<Variable, Type>> it = this.entrySet().iterator();
        System.out.print("{");
        while (it.hasNext()) {
            Map.Entry<Variable, Type> entry = it.next();
            System.out.print("<" + entry.getKey() + ", " + entry.getValue() + ">"); // type map에 저장된 <변수, 변수형> 정보를 출력
            if (it.hasNext())
                System.out.print(", ");
        }
        System.out.println("}\n");
    }
}
