package dbp._2.repository;

import dbp._2.entity.Dept; // Dept.java 경로
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;

import javax.swing.text.html.Option;
import java.util.List;
import java.util.Optional;

public interface DeptRepository extends JpaRepository<Dept, Long> {

    @Query(value = "from Dept where name=?1") // name으로 검색
    public Optional<Dept> findDeptByName(String name);

    @Query(value = "from Dept where building=?1")
    public List<Dept> findDeptByBuilding(String building);

}


