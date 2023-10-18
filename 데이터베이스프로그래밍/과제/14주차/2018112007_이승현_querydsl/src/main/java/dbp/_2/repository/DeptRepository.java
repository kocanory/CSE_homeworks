package dbp._2.repository;

import dbp._2.entity.Dept; // Dept.java 경로
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;

import javax.swing.text.html.Option;
import java.util.List;
import java.util.Optional;

public interface DeptRepository extends JpaRepository<Dept, Long> {

    public Optional<Dept> findDeptByName(String name);

    public List<Dept> findDeptByBuilding(String building);

}


