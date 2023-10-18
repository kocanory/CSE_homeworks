package dbp.UnivQuerydsl.repository;

import dbp.UnivQuerydsl.entity.Dept; // Dept.java 경로
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;
import java.util.Optional;

public interface DeptRepository extends JpaRepository<Dept, Long> {
    public Optional<Dept> findDeptByName(String name);

}


