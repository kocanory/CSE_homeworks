package dbp.UnivJpql.entity;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import javax.persistence.*;

@Entity
@Data
@AllArgsConstructor
@NoArgsConstructor
public class Student {
    @Id
    private Long id;
    private String name;
    private String address;

    @ManyToOne(targetEntity = Dept.class)   // 다대일(N:1) 매핑
    @JoinColumn(name = "did", foreignKey = @ForeignKey(name = "fk_student_did"))
    private Dept dept;
}

